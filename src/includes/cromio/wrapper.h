//
// Created by Brayhan De Aza on 12/12/25.
//

#pragma once

#include <ast/nodes/ProgramNode.h>
#include <llvm/IR/Module.h>
#include <any>



namespace cromio {
    class Cromio final {
       public:
        Cromio(const int argc, const char* argv[]) {
            getContent(argc, argv);
        }

        void compile();

        static visitor::nodes::ProgramNode testAST(std::string& text);
        static void printAST(const std::any& ast);

       private:
        visitor::nodes::ProgramNode getAST();

        // LLVM
        void processLLVM(const std::any& ast) const;
        void getContent(int argc, const char* argv[]);

        std::string content;
        std::string fileName;
    };
} // namespace cromio
