#ifndef __WHILE_HPP__
#define __WHILE_HPP__

#include "stmt.hpp"
#include "expr.hpp"

class While : public Stmt {
public:
    Expr *expr;
    Stmt *stmt;
    While() {
        expr = NULL;
        stmt = NULL;
    }
    void init(Expr *x, Stmt *s) {
        expr = x;
        stmt = s;
        if (expr->type != Type::Bool) {
            expr->error("boolean required in while");
        }
    }
    void gen(int b, int a) {
        after = a;
        expr->jumping(0, a);
        int label = newlabel();
        emitlabel(label);
        stmt->gen(label, b);
        emit("goto L" + std::to_string(b));
    }
};

#endif