#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <string>
#include <cassert>
#include <iostream>
#include "../lexer/lexer.hpp"

class Node {
    int lexline = 0;
public:
    Node() {
        lexline = Lexer::line;
    }
    static int labels;

    void error(std::string s) {
        throw std::runtime_error("near line " + std::to_string(lexline) + ": " + s);
    }

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

int Node::labels = 0;

#endif