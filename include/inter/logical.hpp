#ifndef __LOGICAL_HPP__
#define __LOGICAL_HPP__

#include "expr.hpp"
#include "temp.hpp"

class Logical : public Expr {
public:
    Expr *expr1, *expr2;
    Logical(Token *tok, Expr *x1, Expr *x2) : Expr(tok, nullptr), expr1(x1), expr2(x2) {}
    virtual void setType() {
        type = check(expr1->type, expr2->type);
        if (type == nullptr) {
            error("type error");
        }
    }
    virtual Type* check(Type *p1, Type *p2) {
        if (p1 == Type::Bool && p2 == Type::Bool) {
            return Type::Bool;
        } else {
            return nullptr;
        }
    }

    std::string toString() {
        return expr1->toString() + " " + op->toString() + " " + expr2->toString();
    }

    virtual void code() {
        expr1->code();
        if (expr2 != nullptr) {
            CgenHelper::emitPush(CgenHelper::ACC);
            expr2->code();
            CgenHelper::emitPop(CgenHelper::T1);
        }
        if (op->tag == Tag::AND) {
            CgenHelper::emitAnd(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else if (op->tag == Tag::OR) {
            CgenHelper::emitOr(CgenHelper::ACC, CgenHelper::T1, CgenHelper::ACC);
        } else if (op->tag == '!') {
            CgenHelper::emitNot(CgenHelper::ACC, CgenHelper::ACC);
            CgenHelper::emitAnd(CgenHelper::ACC, CgenHelper::ACC, "1");
        }
    }
};

#endif