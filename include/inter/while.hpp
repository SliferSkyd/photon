#ifndef __WHILE_HPP__
#define __WHILE_HPP__

#include "stmt.hpp"
#include "expr.hpp"
#include "../cgen/cgenhelper.hpp"
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
        // emit("goto L" + std::to_string(b));
    }

    void code() {
        int before = CgenHelper::newLabel();
        int after = CgenHelper::newLabel();
        CgenHelper::emitLabel(before);
        expr->code();
        CgenHelper::emitBeqz(CgenHelper::ACC, CgenHelper::getLabel(after));
        stmt->code();
        CgenHelper::emitBranch(CgenHelper::getLabel(before));
        CgenHelper::emitLabel(after);
    }
};

#endif