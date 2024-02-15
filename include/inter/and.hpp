#ifndef __AND_HPP__
#define __AND_HPP__

#include "logical.hpp"

class And : public Logical {
public:
    And(Token *tok, Expr *x1, Expr *x2) : Logical(tok, x1, x2) {}
};

#endif