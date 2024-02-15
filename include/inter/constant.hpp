#ifndef __CONSTANT_HPP__
#define __CONSTANT_HPP__

#include "expr.hpp"
class Constant : public Expr {
public:
    Constant(Token *tok, Type *p) : Expr(tok, p) {}
    Constant(int i) : Expr(new Num(i), Type::Int) {}
    static Constant *True;
    static Constant *False;

    void code() {
        if (this == Constant::True) {
            CgenHelper::emitLoadImm(CgenHelper::ACC, "1");
        } else if (this == Constant::False) {
            CgenHelper::emitLoadImm(CgenHelper::ACC, "0");
        } else {
            CgenHelper::emitLoadImm(CgenHelper::ACC, op->toString());
        }
    }    
};

Constant *Constant::True = new Constant(Word::True, Type::Bool);
Constant *Constant::False = new Constant(Word::False, Type::Bool);

#endif