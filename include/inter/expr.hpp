#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <string>
#include "node.hpp"
#include "../lexer/token.hpp"
#include "../symbols/type.hpp"

class Expr : public Node {
public:
    Token *op;
    Type *type;
    
    Expr(Token *tok, Type *p) : op(tok), type(p) {}

    virtual void setType() {}
    virtual Expr* gen() {
        return this;
    }
    virtual Expr* reduce() {
        return this;
    }
    virtual void jumping(int t, int f) {
        emitJumps(toString(), t, f);
    }
    void emitJumps(std::string test, int t, int f) {
        if (t != 0 && f != 0) {
            emit("if " + test + " goto L" + std::to_string(t));
            emit("goto L" + std::to_string(f));
        } else if (t != 0) emit("if " + test + " goto L" + std::to_string(t));
        else if (f != 0) emit("iffalse " + test + " goto L" + std::to_string(f));
    }
    virtual std::string toString() {
        return op->toString();
    }
};

#endif