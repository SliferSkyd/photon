#ifndef __DO_HPP__
#define __DO_HPP__

#include "stmt.hpp"
#include "expr.hpp"

class Do : public Stmt {
private:
    Expr *expr;
    Stmt *stmt;
public:
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
    void code() {
        int before = CgenHelper::newLabel();
        int after = CgenHelper::newLabel();
        CgenHelper::emitLabel(before);
        stmt->code();
        expr->code();
        CgenHelper::emitBnez(CgenHelper::ACC, CgenHelper::getLabel(before));
        CgenHelper::emitLabel(after);
    }
};

#endif