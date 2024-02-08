#ifndef __SET_HPP__
#define __SET_HPP__

#include "stmt.hpp"
#include "id.hpp"
#include "expr.hpp"

class Set : public Stmt {
public:
    Id *id;
    Expr *expr;

    Set(Id *i, Expr *x) {
        id = i;
        expr = x;
        if (check(id->type, expr->type) == nullptr) {
            error("type error");
        }
    }

    Type* check(Type *p1, Type *p2) {
        if (Type::numeric(p1) && Type::numeric(p2)) return p2;
        else if (p1 == Type::Bool && p2 == Type::Bool) return p2;
        else return nullptr;
    }

    void gen(int b, int a) {
        emit(id->toString() + " = " + expr->gen()->toString());
    }
};

#endif