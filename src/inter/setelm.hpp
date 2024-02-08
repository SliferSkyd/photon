#ifndef __SET_ELM_HPP__
#define __SET_ELM_HPP__

#include "stmt.hpp"
#include "id.hpp"
#include "expr.hpp"
#include "../symbols/array.hpp"

class SetElm : public Stmt {
public:
    Id *array;
    Expr *index;
    Expr *expr;

    SetElm(Access *x, Expr *y) {
        array = x->array;
        index = x->index;
        expr = y;
        if (check(x->type, expr->type) == nullptr) {
            error("type error");
        }
    }

    Type* check(Type *p1, Type *p2) {
        if ((typeid(*p1) == typeid(Array)) || (typeid(*p2) == typeid(Array))) return nullptr;
        else if (p1 == p2) return p2;
        else if (Type::numeric(p1) && Type::numeric(p2)) return p2;
        else return nullptr;
    }

    void gen(int b, int a) {
        std::string s1 = index->reduce()->toString();
        std::string s2 = expr->reduce()->toString();

        emit(array->toString() + " [" + s1 + "] = " + s2);
    }
};

#endif