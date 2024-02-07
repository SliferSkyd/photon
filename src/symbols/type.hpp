#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <string>
#include "../lexer/word.hpp"
#include "../lexer/tag.hpp"
#include "../lexer/token.hpp"

class Type : public Word {
public:
    int width;
    Type() : Word("", Tag::BASIC), width(0) {}
    Type(std::string s, int tag, int w) : Word(s, tag), width(w) {}
    std::string toString() {
        return lexeme;
    }
    static Type *Int, *Float, *Char, *Bool;

    static bool numeric(Type *p) {
        return p == Type::Char || p == Type::Int || p == Type::Float;
    }

    static Type* max(Type *p1, Type *p2) {
        if (!numeric(p1) || !numeric(p2)) {
            return nullptr;
        } else if (p1 == Type::Float || p2 == Type::Float) {
            return Type::Float;
        } else if (p1 == Type::Int || p2 == Type::Int) {
            return Type::Int;
        } else {
            return Type::Char;
        }
    }
};

Type* Type::Int = new Type("int", Tag::BASIC, 4);
Type* Type::Float = new Type("float", Tag::BASIC, 8);
Type* Type::Char = new Type("char", Tag::BASIC, 1);
Type* Type::Bool = new Type("bool", Tag::BASIC, 1);

#endif