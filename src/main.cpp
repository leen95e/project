#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "lexer.h"
#include "parser.h"
#include "optimizer.h"

int main(int argc, char* argv[]) {
    std::string source = "y = 8 - 3 - 2;";
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
        std::vector<Token> tokens = tokenize(source);     // 1. Lexer
        Parser parser(tokens);
        Program program = parser.parseProgram();          // 2. Parser -> AST
        std::cout << "--- before ---\n";
        for (const Assign& stmt : program)
            std::cout << stmt.name << " = " << stmt.value->toString() << "\n";

        optimize(program);                                // 3. Optimizer

        std::cout << "--- after ---\n";
        for (const Assign& stmt : program)
            std::cout << stmt.name << " = " << stmt.value->toString() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}