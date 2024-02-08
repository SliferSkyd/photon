#ifndef __ACCESS_HPP__
#define __ACCESS_HPP__

#include "op.hpp"
#include "id.hpp"
#include "../lexer/word.hpp"

class Access : public Op {
public:
    Id *array;
    Expr *index;
    Access(Id *a, Expr *i, Type *p) : Op(new Word("[]", Tag::INDEX), p) {
        array = a;
        index = i;
    }
    Expr* gen() {
        return new Access(array, index->reduce(), type);
    }
    void jumping(int t, int f) {
        emitJumps(reduce()->toString(), t, f);
    }
    std::string toString() {
        return array->toString() + " [ " + index->toString() + " ]";
    }
};

#endif