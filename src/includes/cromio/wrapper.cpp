//
// Created by Brayhan De Aza on 12/12/25.
//

#include "wrapper.h"

#include <Grammar.h>
#include <Tokens.h>
#include <ast/program/ProgramVisitor.h>
#include <core/llvm/emitter/CodeEmitter.h>
#include <core/llvm/ir/IR.h>
#include <utils/errors/AntlrErrorListener.h>

#include "antlr4-runtime.h"

#include <fstream>
#include <sstream>
#include <string>

namespace cromio {
    void Cromio::compile() {
        const std::any ast = getAST();
        printAST(ast);

        // const llvm::Module* module = getLLVMModule(ast);
        // printIR(*module);
    }

    std::string Cromio::getContent(const int argc, const char* argv[]) {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            std::exit(1);
        }

        const std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Error: Could not open file " << argv[1] << std::endl;
            std::exit(1);
        }

        std::string filenamePath = argv[1];
        std::string fileName = filenamePath.substr(filenamePath.find_last_of('/') + 1);

        // Remove extension for output name
        std::string baseName = fileName.substr(0, fileName.find_last_of('.'));

        std::stringstream buffer;
        buffer << file.rdbuf();

        std::string content = buffer.str();
        return content;
    }

    std::any Cromio::getAST() {
        // ---------------------------------------------
        // Feed file content into ANTLR
        // ---------------------------------------------
        antlr4::ANTLRInputStream input(content);

        // ---------------------------------------------
        // Feed ANTLR into Tokens
        // ---------------------------------------------
        Tokens lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        Grammar grammar(&tokens);

        // ---------------------------------------------
        // Setup error listeners
        // ---------------------------------------------
        lexer.removeErrorListeners();
        grammar.removeErrorListeners();

        utils::errors::AntlrErrorListener errorListener(content);
        lexer.addErrorListener(&errorListener);
        grammar.addErrorListener(&errorListener);

        // ---------------------------------------------
        // Feed Tokens into Grammar
        // ---------------------------------------------
        auto* tree = grammar.program();
        visitor::Visitor visitor(content, &grammar);

        // ---------------------------------------------
        // Feed Grammar into Visitor and generate AST
        // ---------------------------------------------
        auto ast = visitor.visit(tree);
        return ast;
    }

    void Cromio::printAST(const std::any& ast) {
        if (ast.type() == typeid(visitor::nodes::ProgramNode)) {
            std::cout << "=== AST ===" << std::endl;

            utils::Helpers::printNode(ast, 0);
            std::cout << std::endl << std::endl;

        } else {
            std::cerr << "Error: Expected ProgramNode at root" << std::endl;
            std::exit(1);
        }
    }

    void Cromio::printIR(const llvm::Module& module) {
        std::cout << "=== LLVM IR ===" << std::endl;
        module.print(llvm::outs(), nullptr);
        std::cout << std::endl;
    }

    // const llvm::Module* Cromio::getLLVMModule(const std::any& ast) const {
    //     auto programNode = std::any_cast<visitor::nodes::ProgramNode>(ast);
    //
    //     // lowering::IR ir(fileName);
    //     // const llvm::Module* module = ir.generate(programNode);
    //
    //     // ---------------------------------------------
    //     // Generate executable
    //     // ---------------------------------------------
    //     // cromio::lowering::CodeEmitter::toExecutable(module, baseName);
    //     // std::cout << "Executable generated successfully!" << std::endl;
    //
    //     return module;
    // }

} // namespace cromio
