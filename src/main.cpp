#include <iostream>
#include <fstream>
#include "parser/parser.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string content;
    std::ifstream file(argv[1]);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
    Lexer *lexer = new Lexer();
    Parser *parser = new Parser(lexer);
    try {
        parser->program();
        std::cout << "Compilation successful" << std::endl;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}   