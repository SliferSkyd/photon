#ifndef __NOT_HPP__
#define __NOT_HPP__

#include "logical.hpp"

class Not : public Logical {
public:
    Not(Token *tok, Expr *x2) : Logical(tok, x2, x2) {}
    void jumping(int t, int f) {
        expr2->jumping(t, f);
    }
    std::string toString() {
        return op->toString() + " " + expr2->toString();
    }
};

#endif