#ifndef __REAL_HPP__
#define __REAL_HPP__

#include "token.hpp"
#include "tag.hpp"

class Real : public Token {
public:
    const float value;
    Real(float v) : Token(Tag::REAL), value(v) {}
    std::string toString() {
        return std::to_string(value);
    }
};

#endif