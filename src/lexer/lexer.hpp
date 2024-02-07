#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <string>
#include <vector>
#include <map>
#include "tag.hpp"
#include "token.hpp"
#include "word.hpp"
#include "num.hpp"

class Lexer {
public:
    int line = 1;
    char peek = ' ';
    std::map<std::string, Word> words;
    void reserve(Word w) {
        words.emplace(w.lexeme, w);
    }
    Lexer() {
        reserve(Word("if", Tag::IF));
        reserve(Word("else", Tag::ELSE));
        reserve(Word("while", Tag::WHILE));
        reserve(Word("do", Tag::DO));
        reserve(Word("break", Tag::BREAK));
        reserve(Word::True);
        reserve(Word::False);
    }

    void readch() {
        peek = getchar();
    }

    bool readch(char c) {
        readch();
        if (peek != c) return false;
        peek = ' ';
        return true;
    }

    Token scan() {
        for (; ; readch()) {
            if (peek == ' ' || peek == '\t') continue;
            if (peek == '\n') line++;
            else break;
        }
        switch (peek) {
            case '&':
                if (readch('&')) return Word::And;
                else return Token('&');
            case '|':
                if (readch('|')) return Word::Or;
                else return Token('|');
            case '=':
                if (readch('=')) return Word::eq;
                else return Token('=');
            case '!':
                if (readch('=')) return Word::ne;
                else return Token('!');
            case '<':
                if (readch('=')) return Word::le;
                else return Token('<');
            case '>':
                if (readch('=')) return Word::ge;
                else return Token('>');
        }
        if (peek >= '0' && peek <= '9') {
            int v = 0;
            do {
                v = 10 * v + (peek - '0');
                readch();
            } while (peek >= '0' && peek <= '9');
        
            if (peek != '.') return Num(v);
            float x = v, d = 10;
            for (; ;) {
                readch();
                if (peek < '0' || peek > '9') break;
                x += (peek - '0') / d;
                d *= 10;
            }
            return Real(x);
        }
        if ((peek >= 'a' && peek <= 'z') || (peek >= 'A' && peek <= 'Z')) {
            std::string buffer;
            do {
                buffer.push_back(peek);
                readch();
            } while (peek >= 'a' && peek <= 'z' || peek >= 'A' && peek <= 'Z' || peek >= '0' && peek <= '9');
            auto it = words.find(buffer);
            if (it != words.end()) return it->second;
            Word w = Word(buffer, Tag::ID);
            words.emplace(buffer, w);
            return w;
        }
        Token t = Token(peek);
        peek = ' ';
        return t;
    }
};

#endif