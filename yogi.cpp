//
// Created by Brayhan De Aza on 5/4/26.
//

#include <iostream>
#include <filesystem>
#include "compiler/compiler.h"
#include "utils/helpers/Helpers.h"

int main(const int argc, const char *argv[]) {
    try {
        // Modules Paths Scanner
        yogi::compiler::scanner::Scanner scanner(argc, argv);
        auto modules = scanner.scan();


        // // Compiler
        yogi::compiler::Compiler compiler(argc, argv);
        const yogi::visitor::nodes::ASTNode ast = compiler.compile();
        //
        // // Print AST
        // compiler.printAST(ast.program);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}