#ifndef __UNARY_HPP__
#define __UNARY_HPP__

#include "op.hpp"

class Unary : public Op {
public:
    Expr *expr;
    Unary(Token *tok, Expr *x) : Op(tok, nullptr), expr(x) {
        type = Type::max(Type::Int, expr->type);
        if (type == nullptr) {
            error("type error");
        }
    }
    Expr* gen() {
        return new Unary(op, expr->reduce());
    }
    std::string toString() {
        return op->toString() + " " + expr->toString();
    }

    void code() {
        expr->code();
        if (op->toString() == "-") {
            CgenHelper::emitNeg(CgenHelper::ACC, CgenHelper::ACC);
        } else if (op->toString() == "!") {
            CgenHelper::emitNor(CgenHelper::ACC, CgenHelper::ACC, CgenHelper::ZERO);
        }
    }
};

#endif