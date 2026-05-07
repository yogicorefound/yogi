//
// Created by Brayhan De Aza on 5/4/26.
//

#include <iostream>
#include <filesystem>
#include "compiler/compiler.h"

int main(const int argc, const char *argv[]) {
    try {
        yogi::compiler::Compiler compiler(argc, argv);

        const yogi::visitor::nodes::ASTNode ast = compiler.compile();
        std::cout << ast.path << std::endl;

        // yogi::Yogi::printAST(ast.program);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}