#ifndef __OP_HPP__
#define __OP_HPP__

#include "expr.hpp"
#include "../lexer/token.hpp"
#include "../symbols/type.hpp"
#include "temp.hpp"

class Op : public Expr {
public:
    Token *op;
    Type *type;
    Op(Token *tok, Type *p) : Expr(tok, p), op(tok), type(p) {}
    Expr* reduce() {
        Expr *x = gen();
        Temp *t = new Temp(type);
        emit(t->toString() + " = " + x->toString());
        return t;
    }
};

#endif