#ifndef __IF_HPP__
#define __IF_HPP__

#include "stmt.hpp"
#include "expr.hpp"
#include "../cgen/cgenhelper.hpp"

class If : public Stmt {
public:
    Expr *expr;
    Stmt *stmt;
    If(Expr *x, Stmt *s) {
        expr = x;
        stmt = s;
        if (expr->type != Type::Bool) {
            expr->error("boolean required in if");
        }
    }
    void gen(int b, int a) {
        int label = newlabel();
        expr->jumping(0, a);
        emitlabel(label);
        stmt->gen(label, a);
    }
    void code() {
        int label = CgenHelper::newLabel();
        expr->code();
        CgenHelper::emitBeqz(CgenHelper::ACC, CgenHelper::getLabel(label));
        stmt->code();
        CgenHelper::emitLabel(label);
    }
};

#endif