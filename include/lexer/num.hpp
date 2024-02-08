#ifndef __NUM_HPP__
#define __NUM_HPP__

#include "token.hpp"
#include "tag.hpp"
#include <string>

class Num : public Token {
public:
    const int value;
    Num(int v) : Token(Tag::NUM), value(v) {}
    std::string toString() {
        return std::to_string(value);
    }
};

#endif