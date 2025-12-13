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
        const visitor::nodes::ProgramNode ast = getAST();
        processLLVM(ast);
    }

    void Cromio::getContent(const int argc, const char* argv[]) {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            std::exit(1);
        }

        const std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Error: Could not open file " << argv[1] << std::endl;
            std::exit(1);
        }

        std::string filePath = argv[1];
        fileName = filePath.substr(filePath.find_last_of('/') + 1);

        std::stringstream buffer;
        buffer << file.rdbuf();
        this->content = buffer.str();
    }

    visitor::nodes::ProgramNode Cromio::getAST() {
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
        auto node = std::any_cast<visitor::nodes::ProgramNode>(ast);

        return node;
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

    void Cromio::processLLVM(const std::any& ast) const {
        const auto node = std::any_cast<visitor::nodes::ProgramNode>(ast);

        core::ir::IR ir(fileName);
        llvm::Module* module = ir.generate(node);

        std::cout << "=== LLVM IR ===" << std::endl;
        module->print(llvm::outs(), nullptr);

        // ---------------------------------------------
        // Generate executable
        // ---------------------------------------------
        const std::string baseName = fileName.substr(0, fileName.find_last_of('.'));
        lowering::CodeEmitter::toExecutable(module, baseName);
    }

} // namespace cromio
