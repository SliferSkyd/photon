#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <string>
#include "../lexer/token.hpp"
#include "../lexer/tag.hpp"

class Type : public Token {
public:
    const std::string lexeme;
    const int width;
    Type() : Token(Tag::BASIC), lexeme(""), width(0) {}
    Type(std::string s, int tag, int w) : Token(tag), lexeme(s), width(w) {}
    std::string toString() {
        return lexeme;
    }
    static Type Int, Float, Char, Bool;

    bool operator==(const Type& other) const {
        return lexeme == other.lexeme;
    }

    bool operator!=(const Type& other) const {
        return lexeme != other.lexeme;
    }

    static bool numeric(const Type& p) {
        return p == Type::Char || p == Type::Int || p == Type::Float;
    }

    static Type max(const Type& p1, const Type& p2) {
        if (!numeric(p1) || !numeric(p2)) {
            return Type();
        } else if (p1 == Type::Float || p2 == Type::Float) {
            return Type::Float;
        } else if (p1 == Type::Int || p2 == Type::Int) {
            return Type::Int;
        } else {
            return Type::Char;
        }
    }
};

Type Int("int", Tag::BASIC, 4);
Type Type::Float("float", Tag::BASIC, 8);
Type Type::Char("char", Tag::BASIC, 1);
Type Type::Bool("bool", Tag::BASIC, 1);

#endif