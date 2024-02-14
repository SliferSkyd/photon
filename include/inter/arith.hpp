#ifndef __ARITH_HPP__
#define __ARITH_HPP__

#include "expr.hpp"
#include "../lexer/token.hpp"
#include "../symbols/type.hpp"
#include "op.hpp"

class Arith : public Op {
private:
    Expr *expr1, *expr2;
public:
    Arith(Token *tok, Expr *x1, Expr *x2) : Op(tok, NULL), expr1(x1), expr2(x2) {
        type = Type::max(expr1->type, expr2->type);
        if (type == NULL) {
            error("type error");
        }
    }
    
    Expr* gen() {
        return new Arith(op, expr1->reduce(), expr2->reduce());
    }

    std::string toString() {
        return expr1->toString() + " " + op->toString() + " " + expr2->toString();
    }

    void code() {
        expr1->code();
        CgenHelper::emitPush(CgenHelper::ACC);
        expr2->code();
        CgenHelper::emitPop(CgenHelper::T1);
        if (op->toString() == "+") {
            CgenHelper::emitAdd(CgenHelper::ACC, CgenHelper::ACC, CgenHelper::T1);        
        } else if (op->toString() == "-") {
            CgenHelper::emitSub(CgenHelper::ACC, CgenHelper::ACC, CgenHelper::T1);
        } else if (op->toString() == "*") {
            CgenHelper::emitMul(CgenHelper::ACC, CgenHelper::ACC, CgenHelper::T1);
        } else {
            error("unknown operator");
        }
    }
};

#endif