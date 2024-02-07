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
    static Word *And, *Or, *Eq, *Ne, *Le, *Ge, *Minus, *True, *False, *Temp;
};

Word *Word::And = new Word("&&", Tag::AND);
Word *Word::Or = new Word("||", Tag::OR);
Word *Word::Eq = new Word("==", Tag::EQ);
Word *Word::Ne = new Word("!=", Tag::NE);
Word *Word::Le = new Word("<=", Tag::LE);
Word *Word::Ge = new Word(">=", Tag::GE);
Word *Word::Minus = new Word("minus", Tag::MINUS);
Word *Word::True = new Word("true", Tag::TRUE);
Word *Word::False = new Word("false", Tag::FALSE);
Word *Word::Temp = new Word("t", Tag::TEMP);

#endif