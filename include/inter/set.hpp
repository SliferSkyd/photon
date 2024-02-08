#ifndef __SET_HPP__
#define __SET_HPP__

#include "stmt.hpp"
#include "id.hpp"
#include "expr.hpp"
#include "constant.hpp"

class Set : public Stmt {
public:
    Id *id;
    Expr *expr;

    Set(Id *i, Expr *x) {
        id = i;
        expr = x;
        if (check(id->type, expr->type) == NULL) {
            error("type error");
        }
    }

    Set(Id *i) {
        id = i;
        if (i->type == Type::Int) {
            expr = new Expr(new Num(0), Type::Int);
        } else if (i->type == Type::Float) {
            expr = new Expr(new Real(0.0), Type::Float);
        } else if (i->type == Type::Bool) {
            expr = new Expr((Token*)Constant::False, Type::Bool);
        } else {
            error("type error");
        }
    }

    Type* check(Type *p1, Type *p2) {
        if (Type::numeric(p1) && Type::numeric(p2)) return p2;
        else if (p1 == Type::Bool && p2 == Type::Bool) return p2;
        else return NULL;
    }

    void gen(int b, int a) {
        emit(id->toString() + " = " + expr->gen()->toString());
    }
};

#endif