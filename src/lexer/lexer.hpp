#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <string>
#include <vector>
#include <map>
#include "tag.hpp"
#include "token.hpp"
#include "word.hpp"
#include "num.hpp"
#include "real.hpp"

class Lexer {
public:
    static int line;
    char peek = ' ';
    std::map<std::string, Word*> words;
    void reserve(Word *w) {
        words[w->lexeme] = w;
    }
    Lexer() {
        reserve(new Word("if", Tag::IF));
        reserve(new Word("else", Tag::ELSE));
        reserve(new Word("while", Tag::WHILE));
        reserve(new Word("do", Tag::DO));
        reserve(new Word("break", Tag::BREAK));
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

    Token* scan() {
        for (; ; readch()) {
            if (peek == ' ' || peek == '\t') continue;
            if (peek == '\n') line++;
            else break;
        }
        switch (peek) {
            case '&':
                if (readch('&')) return Word::And;
                else return new Token('&');
            case '|':
                if (readch('|')) return Word::Or;
                else return new Token('|');
            case '=':
                if (readch('=')) return Word::Eq;
                else return new Token('=');
            case '!':
                if (readch('=')) return Word::Ne;
                else return new Token('!');
            case '<':
                if (readch('=')) return Word::Le;
                else return new Token('<');
            case '>':
                if (readch('=')) return Word::Ge;
                else return new Token('>');
        }
        if (peek >= '0' && peek <= '9') {
            int v = 0;
            do {
                v = 10 * v + (peek - '0');
                readch();
            } while (peek >= '0' && peek <= '9');
        
            if (peek != '.') return new Num(v);
            float x = v, d = 10;
            for (; ;) {
                readch();
                if (peek < '0' || peek > '9') break;
                x += (peek - '0') / d;
                d *= 10;
            }
            return new Real(x);
        }
        if ((peek >= 'a' && peek <= 'z') || (peek >= 'A' && peek <= 'Z')) {
            std::string buffer;
            do {
                buffer.push_back(peek);
                readch();
            } while (peek >= 'a' && peek <= 'z' || peek >= 'A' && peek <= 'Z' || peek >= '0' && peek <= '9');
            auto it = words.find(buffer);
            if (it != words.end()) return it->second;
            Word *w = new Word(buffer, Tag::ID);
            words[buffer] = w;
            return w;
        }
        Token *t = new Token(peek);
        peek = ' ';
        return t;
    }
};

int Lexer::line = 1;

#endif