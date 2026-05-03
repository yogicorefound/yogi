//
// Created by Brayhan De Aza on 5/2/26.
//

// linker.cpp
#include "linker.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>

using namespace llvm;

void Linker::registerNativeFunction(Module *module,const std::string &name,FunctionType *type) {
    Function::Create(type,Function::ExternalLinkage,name,module);
}