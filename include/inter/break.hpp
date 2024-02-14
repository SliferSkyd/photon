#ifndef __BREAK_HPP__
#define __BREAK_HPP__

#include "stmt.hpp"
#include "../cgen/cgenhelper.hpp"

class Break : public Stmt {
public:
    Stmt *stmt;
    Break() {
        if (Stmt::Enclosing == Stmt::Null) error("unenclosed break");
        stmt = Stmt::Enclosing;
    }
    void gen(int b, int a) {
        // emit("goto L" + std::to_string(stmt->after));
        CgenHelper::emitBranch("L" + std::to_string(stmt->after));
    }
};

#endif