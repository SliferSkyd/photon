#ifndef __DO_HPP__
#define __DO_HPP__

#include "stmt.hpp"
#include "expr.hpp"

class Do : public Stmt {
public:
    Expr *expr;
    Stmt *stmt;
    Do() {
        expr = NULL;
        stmt = NULL;
    }
    void init(Stmt *s, Expr *x) {
        expr = x;
        stmt = s;
        if (expr->type != Type::Bool) {
            expr->error("boolean required in do");
        }
    }
    void gen(int b, int a) {
        after = a;
        int label = newlabel();
        stmt->gen(b, label);
        emitlabel(label);
        expr->jumping(b, 0);
    }
};

#endif