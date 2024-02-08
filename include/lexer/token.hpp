#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <string>

class Token {
public:
    const int tag;
    Token(int t) : tag(t) {}
    virtual std::string toString() {
        return std::string(1, (char) tag);
    }
};

#endif