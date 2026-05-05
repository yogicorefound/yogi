//
// Created by Brayhan De Aza on 5/2/26.
//

#pragma once

#include <llvm/IR/Module.h>
#include <any>
#include <visitors/nodes/ProgramNode.h>
#include "../src/visitors/arrays/ArraysVisitor.h"

namespace yogi {
    class Compiler final {
        public:
            Compiler(const int argc, const char *argv[]) {
                getContent(argc, argv);
            }

            void compile();

            static visitor::nodes::ProgramNode testAST(std::string &text);

            static void printAST(const std::any &ast);

        private:
            visitor::nodes::ProgramNode getAST();

            // LLVM
            void processLLVM(const std::any &ast) const;

            void getContent(int argc, const char *argv[]);

            std::string content;
            std::string fileName;
    };
} // namespace yogi