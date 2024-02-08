#ifndef __CONSTANT_HPP__
#define __CONSTANT_HPP__

#include "expr.hpp"

class Constant : public Expr {
public:
    Constant(Token *tok, Type *p) : Expr(tok, p) {}
    Constant(int i) : Expr(new Num(i), Type::Int) {}
    static Constant *True;
    static Constant *False;
    
    void jumping(int t, int f) {
        if (this == True && t != 0) {
            emit("goto L" + std::to_string(t));
        } else if (this == False && f != 0) {
            emit("goto L" + std::to_string(f));
        }
    }
};

Constant *Constant::True = new Constant(Word::True, Type::Bool);
Constant *Constant::False = new Constant(Word::False, Type::Bool);

#endif