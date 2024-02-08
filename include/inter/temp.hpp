#ifndef __TEMP_HPP__
#define __TEMP_HPP__

#include <string>
#include "expr.hpp"

class Temp : public Expr {
public:
    static int count;
    int number;
    Temp(Type *p) : Expr(Word::Temp, p) {
        number = ++count;
    }
    std::string toString() {
        return "t" + std::to_string(number);
    }
};

int Temp::count = 0;

#endif