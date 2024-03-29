#include <iostream>
#include <fstream>
#include "../include/parser/parser.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return EXIT_FAILURE;
    }
    freopen(argv[2], "w", stdout);
    
    Lexer *lexer = new Lexer(argv[1]);
    Parser *parser = new Parser(lexer);
    parser->program();
}   