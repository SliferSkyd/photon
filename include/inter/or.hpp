#ifndef __OR_HPP__
#define __OR_HPP__

#include "logical.hpp"

class Or : public Logical {
public:
    Or(Token *tok, Expr *x1, Expr *x2) : Logical(tok, x1, x2) {}
};

#endif