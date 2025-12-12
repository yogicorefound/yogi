//
// Created by Brayhan De Aza on 12/12/25.
//

#pragma once

#include <llvm/IR/Module.h>
#include <any>

namespace cromio {
    class Cromio final {
       public:
        Cromio(const int argc, const char* argv[]) : content(getContent(argc, argv)) {}

        void compile();

       private:
        std::any getAST();
        static void printAST(const std::any& ast);

        // LLVM
        const llvm::Module* getLLVMModule(const std::any& ast) const;
        static void printIR(const llvm::Module& module);
        static std::string getContent(int argc, const char* argv[]);

        std::string content;
        std::string fileName;
    };
} // namespace cromio
