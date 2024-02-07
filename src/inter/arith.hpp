#ifndef __ARITH_HPP__
#define __ARITH_HPP__

#include "expr.hpp"
#include "../lexer/token.hpp"
#include "../symbols/type.hpp"
#include "op.hpp"

class Arith : public Op {
public:
    Expr *expr1, *expr2;
    Arith(Token *tok, Expr *x1, Expr *x2) : Op(tok, nullptr), expr1(x1), expr2(x2) {
        type = Type::max(expr1->type, expr2->type);
        if (type == nullptr) {
            error("type error");
        }
    }
    
    Expr* gen() {
        return new Arith(op, expr1->reduce(), expr2->reduce());
    }

    std::string toString() {
        return expr1->toString() + op->toString() + expr2->toString();
    }
};

#endif