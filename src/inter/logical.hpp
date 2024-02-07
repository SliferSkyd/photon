#ifndef __LOGICAL_HPP__
#define __LOGICAL_HPP__

#include "expr.hpp"
#include "temp.hpp"

class Logical : public Expr {
public:
    Expr *expr1, *expr2;
    Logical(Token *tok, Expr *x1, Expr *x2) : Expr(tok, nullptr), expr1(x1), expr2(x2) {
        type = check(expr1->type, expr2->type);
        if (type == nullptr) {
            error("type error");
        }
    }
    Type* check(Type *p1, Type *p2) {
        if (p1 == Type::Bool && p2 == Type::Bool) {
            return Type::Bool;
        } else {
            return nullptr;
        }
    }
    Expr* gen() {
        int f = newlabel(), a = newlabel();
        Temp *temp = new Temp(type);
        this->jumping(0, f);
        emit(temp->toString() + " = true");
        emit("goto L" + std::to_string(a));
        emitlabel(f); 
        emit(temp->toString() + " = false");
        emitlabel(a);
        return temp;
    }

    std::string toString() {
        return expr1->toString() + " " + op->toString() + " " + expr2->toString();
    }
};

#endif