#ifndef __FLOAT_HPP__
#define __FLOAT_HPP__

#include "token.hpp"
#include "tag.hpp"
#include <string>

class Float : public Token {
public:
    const float value;
    Float(float v) : Token(Tag::REAL), value(v) {}
    std::string toString() {
        return std::to_string(value);
    }
};

#endif