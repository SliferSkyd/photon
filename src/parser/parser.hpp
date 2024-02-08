#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "../lexer/lexer.hpp"
#include "../lexer/token.hpp"
#include "../symbols/env.hpp"
#include "../inter/stmt.hpp"
#include "../symbols/array.hpp"
#include "../inter/seq.hpp"
#include "../inter/if.hpp"
#include "../inter/while.hpp"
#include "../inter/do.hpp"
#include "../inter/break.hpp"
#include "../inter/set.hpp"
#include "../inter/setelm.hpp"
#include "../inter/and.hpp"
#include "../inter/or.hpp"
#include "../inter/rel.hpp"
#include "../inter/expr.hpp"
#include "../inter/id.hpp"
#include "../inter/access.hpp"
#include "../symbols/type.hpp"
#include "../lexer/num.hpp"
#include "../lexer/word.hpp"
#include "../lexer/real.hpp"
#include "../inter/not.hpp"
#include "../inter/unary.hpp"
#include "../inter/constant.hpp"
#include "../inter/arith.hpp"

class Parser {
    Lexer *lex;
    Token *look;
public:
    Env top = nullptr;
    int used = 0;

    Parser(Lexer *l) : lex(l) {
        move();
    }

    void move() {
        look = lex->scan();
    }

    void error(std::string s) {
        throw std::runtime_error("near line " + std::to_string(lex->line) + ": " + s);
    }

    void match(int t) {
        if (look->tag == t) {
            move();
        } else {
            error("syntax error");
        }
    }

    void program() {
        Stmt *s = block();
        int begin = s->newlabel();
        int after = s->newlabel();
        s->emitlabel(begin);
        s->gen(begin, after);
        s->emitlabel(after);
    }

    Stmt* block() {
        match('{');
        Env savedEnv = top;
        top = new Env(top);
        decls();
        Stmt *s = stmts();
        match('}');
        top = savedEnv;
        return s;
    }

    void decls() {
        while (look->tag == Tag::BASIC) {
            Type *p = type();
            Token *tok = look;
            match(Tag::ID);
            match(';');
            Id *id = new Id((Word*)tok, p, used);
            top.put(tok, id);
            used = used + p->width;
        }
    }

    Type* type() {
        Type* p = (Type*) look;
        match(Tag::BASIC);
        if (look->tag != '[') {
            return p;
        } else {
            return dims(p);
        }
    }

    Type* dims(Type *p) {
        match('[');
        Token* tok = look;
        match(Tag::NUM);
        match(']');
        if (look->tag == '[') {
            p = dims(p);
        }
        return new Array(((Num*) tok)->value, p);
    }

    Stmt* stmts() {
        if (look->tag == '}') {
            return Stmt::Null;
        } else {
            return new Seq(stmt(), stmts());
        }
    }

    Stmt* stmt() {
        Expr *x;
        Stmt *s, *s1, *s2;
        Stmt *savedStmt;

        switch (look->tag) {
            case ';':
                move();
                return Stmt::Null;
            case Tag::IF:
                match(Tag::IF); match('('); x = boolean(); match(')');
                s1 = stmt();
                if (look->tag != Tag::ELSE) return new If(x, s1);
                match(Tag::ELSE); 
                s2 = stmt();
            case Tag::WHILE:
                While *whilenode = new While();
                savedStmt = Stmt::Enclosing; Stmt::Enclosing = whilenode;
                match(Tag::WHILE); match('('); x = boolean(); match(')');
                s1 = stmt();
                whilenode->init(x, s1);
                Stmt::Enclosing = whilenode;
            case Tag::DO:
                Do *donode = new Do();
                savedStmt = Stmt::Enclosing; Stmt::Enclosing = donode;
                match(Tag::DO);
                s1 = stmt();
                match(Tag::WHILE); match('('); x = boolean(); match(')'); match(';');
                donode->init(s1, x);
                Stmt::Enclosing = savedStmt;
                return donode;
            case Tag::BREAK:
                match(Tag::BREAK); match(';');
                return new Break();
            case '{':
                return block();
            default:
                return assign();
        }
    }

    Stmt* assign() {
        Stmt *stmt;
        Token *t = look;
        match(Tag::ID);
        Id* id = top.get(t);
        if (id == nullptr) {
            error(t->toString() + " undeclared");
        }
        if (look->tag == '=') {
            move();
            stmt = new Set(id, boolean());
        } else {
            Access* x = offset(id);
            match('=');
            stmt = new SetElm(x, boolean());
        }
        match(';');
        return stmt;
    }

    Expr* boolean() {
        Expr *x = join();
        while (look->tag == Tag::OR) {
            Token *tok = look;
            move();
            x = new Or(tok, x, join());
        }
        return x;
    }
    Expr* join() {
        Expr *x = equality();
        while (look->tag == Tag::AND) {
            Token *tok = look;
            move();
            x = new And(tok, x, equality());
        }
        return x;
    }
    Expr* equality() {
        Expr* x = rel();
        while (look->tag == Tag::EQ || look->tag == Tag::NE) {
            Token *tok = look;
            move();
            x = new Rel(tok, x, rel());            
        }
    }
    Expr* rel() {
        Expr* x = expr();
        switch (look->tag) {
            case '<': case Tag::LE: case Tag::GE: case '>':
                Token *tok = look;
                move();
                return new Rel(tok, x, expr());
            default:
                return x;
        }
    }
    Expr* expr() {
        Expr *x = term();
        while (look->tag == '+' || look->tag == '-') {
            Token *tok = look; move(); x = new Arith(tok, x, term());
        }
        return x;
    }
    Expr* term() {
        Expr *x = unary();
        while (look->tag == '*' || look->tag == '/') {
            Token *tok = look; move(); x = new Arith(tok, x, unary());
        } 
        return x;
    }
    Expr* unary() {
        if (look->tag == '-') {
            move();
            return new Unary(Word::Minus, unary());
        } else if (look->tag == '!') {
            Token *tok = look; move(); 
            return new Not(tok, unary());
        } else return factor();
    }
    Expr* factor() {
        Expr *x = nullptr;
        switch (look->tag) {
            case '(':
                move(); x = boolean(); match(')');
                return x;
            case Tag::NUM:
                x = new Constant(look, Type::Int);
                move();
                return x;
            case Tag::REAL:
                x = new Constant(look, Type::Float);
                move();
                return x;
            case Tag::TRUE:
                x = Constant::True;
                move();
                return x;
            case Tag::FALSE:
                x = Constant::False;
                move();
                return x;
            case Tag::ID:
                Id *id = top.get(look);
                if (id == nullptr) {
                    error(look->toString() + " undeclared");
                }
                move();
                if (look->tag != '[') {
                    return id;
                } else {
                    return offset(id);
                }
            default:
                error("syntax error");
                return x;
        }
    }
    Access* offset(Id *a) {
        Expr *i, *w, *t1, *t2, *loc;
        Type *type = a->type;
        match('['); i = boolean(); match(']');
        type = ((Array*) type)->of;
        w = new Constant(type->width);
        loc = t1;
        while (look->tag == '[') {
            match('['); i = boolean(); match(']');
            type = ((Array*) type)->of;
            w = new Constant(type->width);
            t1 = new Arith(new Token('*'), i, w);
            t2 = new Arith(new Token('+'), loc, w);
            loc = t2;
        }
        return new Access(a, loc, type);
    }
};

#endif