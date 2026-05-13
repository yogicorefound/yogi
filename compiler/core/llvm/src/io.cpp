//
// Created by Brayhan De Aza on 5/13/26.
//

#include "core/llvm/llvm.h"


namespace yogi::compiler::core {
    llvm::Module *LLVM::generateIR(const visitor::nodes::ProgramNode &ast) {
        yogi::core::ir::IR ir("fileName");
        llvm::Module *module = ir.generate(ast);

        module->print(llvm::outs(), nullptr);

        return module;
    }
}