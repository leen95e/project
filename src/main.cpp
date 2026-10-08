#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "lexer.h"

int main(int argc, char* argv[]) {
    std::string source = "x = 3 * (4 + 2);";
    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Cannot open " << argv[1] << "\n";
            return 1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        source = buffer.str();
    }

    try {
        for (const Token& tok : tokenize(source)) {
            std::cout << tokenTypeName(tok.type) << " '" << tok.text << "'\n";
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}