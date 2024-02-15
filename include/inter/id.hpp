#ifndef __ID_HPP__
#define __ID_HPP__

#include <string>
#include "expr.hpp"
#include "../lexer/word.hpp"

class Id : public Expr {
public:
    int offset;
    bool isDefined = false;
    Id(Word *id, Type *p, int b) : Expr(id, p), offset(b) {} 
    void code() {
        if (!isDefined) {
            CgenHelper::emitNumberConstant(op->toString(), "0");
            isDefined = true;
        } else {
            CgenHelper::emitLoad(CgenHelper::ACC, op->toString());
        }
    }
};

#endif