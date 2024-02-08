#ifndef __ID_HPP__
#define __ID_HPP__

#include <string>
#include "expr.hpp"
#include "../lexer/word.hpp"

class Id : public Expr {
public:
    int offset;
    Id(Word *id, Type *p, int b) : Expr(id, p), offset(b) {} 
};

#endif