//
// Created by Brayhan De Aza on 12/12/25.
//

#pragma once

#include <visitors/nodes/ProgramNode.h>
#include <llvm/IR/Module.h>
#include <any>

namespace yogi::compiler {
    class Compiler final {
        public:
            Compiler(const int argc, const char *argv[]) {
                getContent(argc, argv);
            }

            visitor::nodes::ASTNode compile();

            static visitor::nodes::ProgramNode testAST(std::string &text, std::string &filePath);

            static void printAST(const std::any &ast);

            void processLLVM(const std::any &ast) const;

        private:
            visitor::nodes::ProgramNode getAST();

            // LLVM
            void getContent(int argc, const char *argv[]);

            std::string content;
            std::string fileName;
            std::string filePath;
    };
} // namespace yogi