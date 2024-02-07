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
    static Word And, Or, eq, ne, le, ge, minus, True, False, temp;
};

Word Word::And("&&", Tag::AND);
Word Word::Or("||", Tag::OR);
Word Word::eq("==", Tag::EQ);
Word Word::ne("!=", Tag::NE);
Word Word::le("<=", Tag::LE);
Word Word::ge(">=", Tag::GE);
Word Word::minus("minus", Tag::MINUS);
Word Word::True("true", Tag::TRUE);
Word Word::False("false", Tag::FALSE);
Word Word::temp("temp", Tag::TEMP);

#endif