//
// Created by Brayhan De Aza on 12/12/25.
//

#pragma once

#include <visitors/nodes/ProgramNode.h>
#include <llvm/IR/Module.h>
#include <any>
#include "compiler/scanner/Scanner.h"

namespace yogi::compiler {
    class Compiler final {
        public:
            Compiler() = default;

            std::any compile(std::string modulePath);

            static visitor::nodes::ProgramNode testAST(std::string &text, std::string &filePath);

            static void printAST(const std::any &ast);

            void processLLVM(const std::any &ast) const;

            static std::any scan(std::string fPath);

        private:
            std::any getAST(bool justScan);

            // LLVM
            void getContent(int argc, const char *argv[]);

            void getModuleContent(std::string fPath);

            std::string content;
            std::string fileName;
            std::string filePath;
    };
} // namespace yogi