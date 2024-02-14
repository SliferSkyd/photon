#ifndef __REL_HPP__
#define __REL_HPP__

#include "logical.hpp"
#include "../symbols/array.hpp"

class Rel : public Logical {
public:
    Rel(Token *tok, Expr *x1, Expr *x2) : Logical(tok, x1, x2) {}
    Type* check(Type *p1, Type *p2) override {
        if (typeid(*p1) == typeid(Array) || typeid(*p2) == typeid(Array)) {
            return nullptr;
        } else if (p1 == p2) {
            return Type::Bool;
        } else {
            return nullptr;
        }
    }

    void jumping(int t, int f) {
        Expr *a = expr1->reduce();
        Expr *b = expr2->reduce();
        // std::string test = a->toString() + " " + op->toString() + " " + b->toString();
        

        // emitJumps(test, t, f);
    }
    void code() {
        expr1->code();
        CgenHelper::emitPush(CgenHelper::ACC);
        expr2->code();
        CgenHelper::emitPop(CgenHelper::T1);
        if (op->toString() == "==") {
            CgenHelper::emitSeq(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);  
        } else if (op->toString() == "!=") {
            CgenHelper::emitSne(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else if (op->toString() == "<") {
            CgenHelper::emitSlt(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else if (op->toString() == ">") {
            CgenHelper::emitSgt(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else if (op->toString() == "<=") {
            CgenHelper::emitSle(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else if (op->toString() == ">=") {
            CgenHelper::emitSge(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else {
            error("unknown operator");
        }
    }
};

#endif