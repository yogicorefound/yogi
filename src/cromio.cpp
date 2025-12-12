//
// Created by Brayhan De Aza on 11/27/25.
//

#include "includes/cromio/cromio.h"

#include <utils/errors/AntlrErrorListener.h>

int main(int argc, const char* argv[]) {
    try {
        // ---------------------------------------------
        // Load input file
        // ---------------------------------------------
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            return 1;
        }

        // Read file content
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Error: Could not open file " << argv[1] << std::endl;
            return 1;
        }

        std::string filenamePath = argv[1];
        std::string fileName = filenamePath.substr(filenamePath.find_last_of('/') + 1);

        // Remove extension for output name
        std::string baseName = fileName.substr(0, fileName.find_last_of('.'));

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        // ---------------------------------------------
        // Feed file content into ANTLR
        // ---------------------------------------------
        antlr4::ANTLRInputStream input(content);

        Tokens lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        Grammar grammar(&tokens);

        lexer.removeErrorListeners();
        grammar.removeErrorListeners();

        cromio::utils::errors::AntlrErrorListener errorListener(content);
        lexer.addErrorListener(&errorListener);
        grammar.addErrorListener(&errorListener);

        auto* tree = grammar.program();

        cromio::visitor::Visitor visitor(content, &grammar);
        std::any ast = visitor.visit(tree);

        // ---------------------------------------------
        // Print AST (for debugging)
        // ---------------------------------------------
        if (ast.type() == typeid(cromio::visitor::nodes::ProgramNode)) {
            std::cout << "=== AST ===" << std::endl;
            cromio::utils::Helpers::printNode(ast, 0);
            std::cout << std::endl << std::endl;
        } else {
            std::cerr << "Error: Expected ProgramNode at root" << std::endl;
            return 1;
        }

        // // ---------------------------------------------
        // // Extract ProgramNode for LLVM IR generation
        // // ---------------------------------------------
        // auto programNode = std::any_cast<cromio::visitor::nodes::ProgramNode>(ast);
        //
        // // ---------------------------------------------
        // // Emit LLVM IR from AST
        // // ---------------------------------------------
        // cromio::lowering::IR ir(fileName);
        // llvm::Module* module = ir.generate(programNode);  // Pass ProgramNode instead of json
        //
        // // ---------------------------------------------
        // // Print LLVM IR (for debugging)
        // // ---------------------------------------------
        // std::cout << "=== LLVM IR ===" << std::endl;
        // module->print(llvm::outs(), nullptr);
        // std::cout << std::endl;
        //
        // // ---------------------------------------------
        // // Generate executable
        // // ---------------------------------------------
        // cromio::lowering::CodeEmitter::toExecutable(module, baseName);
        // std::cout << "Executable generated successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}