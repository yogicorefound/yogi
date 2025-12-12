//
// Created by Brayhan De Aza on 11/24/25.
//

#ifndef CROMIO_IR_H
#define CROMIO_IR_H

#include <utils/utils.h>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace cromio::lowering {
    class IR {
       public:
        explicit IR(const std::string& moduleName);

        // generate module from AST
        llvm::Module* generate(const json& ast);

       private:
        // core LLVM pieces
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        // symbol table: variable name -> alloca
        std::unordered_map<std::string, llvm::AllocaInst*> symbols;

        // helpers
        llvm::Type* mapDataType(const std::string& typeName) const;
        llvm::Value* promoteToDouble(llvm::Value* v) const;
        llvm::Type* inferType(const json& node) const;

        // codegen units
        static llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, llvm::Type* type, const std::string& name);
        static std::unique_ptr<llvm::Module> loadBitcode(const std::string& path, llvm::LLVMContext& context);

        llvm::Value* literal(const json& node) const;
        llvm::Value* expression(const json& node);
        llvm::Value* variableDeclaration(const json& node);
        llvm::Value* variableAssignment(const json& node);
        llvm::Value* program(const json& node);
        llvm::Value* arrayDeclaration(const json& node);

        void loadAndLinkModulesFromFolder() const;
        bool linkModule(std::unique_ptr<llvm::Module> other) const;
    };
} // namespace cromio::lowering

#endif // CROMIO_IR_H
