#ifndef __FOR_HPP__
#define __FOR_HPP__

#include "stmt.hpp"
#include "expr.hpp"

class For : public Stmt {
public:
    Stmt *declr;
    Expr *cond;
    Stmt *incr;
    Stmt *stmt;

    For() {
        declr = NULL;
        cond = NULL;
        incr = NULL;
        stmt = NULL;
    }
    void init(Stmt *x, Expr *y, Stmt *z, Stmt *s) {
        declr = x;
        cond = y;
        incr = z;
        stmt = s;
        if (cond->type != Type::Bool) {
            cond->error("boolean required in for");
        }
    }
    void gen(int b, int a) {
        after = a;
        declr->gen(b, a);
        int label = newlabel();
        emitlabel(label);
        cond->jumping(0, a);
        int label2 = newlabel();
        emitlabel(label2);
        stmt->gen(label2, label);
        incr->gen(label, b);
        emit("goto L" + std::to_string(label));
    }
};

#endif