#ifndef __AND_HPP__
#define __AND_HPP__

#include "logical.hpp"

class And : public Logical {
public:
    And(Token *tok, Expr *x1, Expr *x2) : Logical(tok, x1, x2) {}
    void jumping(int t, int f) {
        int label = f != 0 ? f : newlabel();
        expr1->jumping(0, label);
        expr2->jumping(t, f);
        if (f == 0) {
            emitlabel(label);
        }
    }
};

#endif