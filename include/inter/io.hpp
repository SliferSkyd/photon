#ifndef __IO_HPP__
#define __IO_HPP__

#include <iostream>
#include <string>
#include "stmt.hpp"
#include "id.hpp"

class IO : public Stmt {
public:
    enum class IOType {
        INPUT,
        OUTPUT
    };
    Expr *expr;
    IOType type;
    IO(Expr *e, IOType t) : expr(e), type(t) {
        if (type == IOType::INPUT) {
            if (dynamic_cast<Id*>(expr) == nullptr) {
                expr->error("expression must be an lvalue");
            }
        }
    }
    void code() {
        if (type == IOType::INPUT) {
            CgenHelper::emitReadInt(expr->op->toString());
        } else {
            expr->code();
            CgenHelper::emitPrintInt();
        }
    }
};

#endif  