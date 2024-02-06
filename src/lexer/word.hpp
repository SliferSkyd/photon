#ifndef __WORD_HPP__
#define __WORD_HPP__

#include <string>
#include "tag.hpp"
#include "token.hpp"

class Word : public Token {
public:
    const std::string lexeme;
    Word(std::string s, int tag) : Token(tag), lexeme(s) {}
    std::string toString() {
        return lexeme;
    }
};

#endif