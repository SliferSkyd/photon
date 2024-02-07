#ifndef __ENV_HPP__
#define __ENV_HPP__

#include <map>
#include <string>
#include "../lexer/token.hpp"
#include "../lexer/token.hpp"


class Env {
public:
    std::map<std::string, Token> table;
    Env* prev;
    Env(Env* n) : prev(n) {}
    void put(std::string w, Id i) {
        table.emplace(w, i);
    }
    Id get(Token w) {
        for (Env* e = this; e != nullptr; e = e->prev) {
            auto found = e->table.find(w.toString());
            if (found != e->table.end()) {
                return found->second;
            }
        }
        return nullptr;
    }
};

#endif