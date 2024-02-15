#ifndef __NOT_HPP__
#define __NOT_HPP__

#include "logical.hpp"

class Not : public Logical {
public:
    Not(Token *tok, Expr *x2) : Logical(tok, x2, nullptr) {}
    void setType() {
        type = check(expr1->type, expr1->type);
        if (type == nullptr) {
            error("type error");
        }
    }
    std::string toString() {
        return op->toString() + " " + expr2->toString();
    }
};

#endif