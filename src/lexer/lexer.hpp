#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <string>
#include <vector>
#include <map>
#include "tag.hpp"
#include "token.hpp"
#include "word.hpp"

class Lexer {
public:
    int line = 1;
    char peek = ' ';
    std::map<std::string, Word> words;
    void reserve(Word w) {
        words[w.lexeme] = w;
    }
    Lexer() {
        reserve(Word("if", Tag::IF));
        reserve(Word("else", Tag::ELSE));
        reserve(Word("while", Tag::WHILE));
        reserve(Word("do", Tag::DO));
        reserve(Word("break", Tag::BREAK));
        
    }
};

#endif