//
// Created by Brayhan De Aza on 5/2/26.
//

#pragma once


#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <unordered_map>
#include <string>
#include <functional>

class Linker {
    public:
        using NativeFn = void(*)(void *);

        static void registerNativeFunction(
            llvm::Module *module,
            const std::string &name,
            llvm::FunctionType *type
        );

        static void bindRuntime();
};