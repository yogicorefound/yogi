//
// Created by Brayhan De Aza on 5/13/26.
//

#pragma once

#include <visitors/nodes/ProgramNode.h>
#include "core/llvm/llvm.h"
#include <core/llvm/ir/IR.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

namespace yogi::compiler::core {
    class LLVM {
        static llvm::Module* generateIR(const visitor::nodes::ProgramNode &ast);

    };

}