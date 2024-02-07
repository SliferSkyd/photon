#ifndef __ENV_HPP__
#define __ENV_HPP__

#include <map>
#include <string>
#include "../lexer/token.hpp"
#include "../inter/id.hpp"

class Env {
public:
    std::map<Token*, Id*> table;
    Env* prev;
    Env(Env* n) : prev(n) {}
    void put(Token *t, Id *i) {
        table[t] = i;
    }
    Id* get(Token *w) {
        for (Env* e = this; e != nullptr; e = e->prev) {
            auto found = e->table.find(w);
            if (found != e->table.end()) {
                return found->second;
            }
        }
        return nullptr;
    }
};

#endif