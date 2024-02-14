#ifndef __ELSE_HPP__
#define __ELSE_HPP__

#include "stmt.hpp"
#include "expr.hpp"
#include "../cgen/cgenhelper.hpp"

class Else : public Stmt {
public:
    Expr *expr;
    Stmt *stmt1, *stmt2;
    Else(Expr *x, Stmt *s1, Stmt *s2) {
        expr = x;
        stmt1 = s1;
        stmt2 = s2;
        if (expr->type != Type::Bool) {
            expr->error("boolean required in if");
        }
    }
    void gen(int b, int a) {
        int label1 = newlabel();
        int label2 = newlabel();
        expr->jumping(0, label2);
        emitlabel(label1); stmt1->gen(label1, a); 
        // emit("goto L" + std::to_string(a));
        CgenHelper::emitBranch("L" + std::to_string(a));
        emitlabel(label2); stmt2->gen(label2, a);
    }
    void code() {
        int label1 = CgenHelper::newLabel();
        int label2 = CgenHelper::newLabel();
        expr->code();
        CgenHelper::emitBeqz(CgenHelper::ACC, CgenHelper::getLabel(label1));
        stmt1->code();
        // emit("goto L" + std::to_string(label2));
        CgenHelper::emitBranch("L" + std::to_string(label2));
        CgenHelper::emitLabel(label1);
        stmt2->code();
        CgenHelper::emitLabel(label2);
    }
};

#endif