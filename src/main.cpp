#include <iostream>
#include <fstream>

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
        std::cout << content << '\n';
    } else {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
}