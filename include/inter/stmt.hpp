#ifndef __STMT_HPP__
#define __STMT_HPP__

#include "node.hpp"

class Stmt : public Node {
public:
    int after = 0;
    static Stmt *Null, *Enclosing;
    Stmt() {}
    virtual void gen(int b, int a) {}
    virtual void code() {}
};

Stmt *Stmt::Null = new Stmt();
Stmt *Stmt::Enclosing = Stmt::Null;

#endif