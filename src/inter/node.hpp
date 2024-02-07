#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <string>
#include <iostream>
#include "../lexer/lexer.hpp"

class Node {
    int lexline = 0;
public:
    Node() {
        lexline = Lexer::line;
    }

    void error(std::string s) {
        throw std::runtime_error("near line " + std::to_string(lexline) + ": " + s);
    }

    static int labels;
    int newlabel() {
        return ++labels;
    }

    void emitlabel(int i) {
        std::cout << "L" << i << ":";
    }

    void emit(std::string s) {
        std::cout << "\t" << s << std::endl;
    }
};

#endif