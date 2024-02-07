#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include <string>
#include "type.hpp"

class Array : public Type {
public:
    Type *of;
    int size = 1;
    Array(int sz, Type *p) : Type("[]", Tag::INDEX, sz * p->width), size(sz), of(p) {}
    std::string toString() {
        return "[" + std::to_string(size) + "] " + of->toString();
    }
};

#endif