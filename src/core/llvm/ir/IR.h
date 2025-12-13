//
// Created by Brayhan De Aza on 11/24/25.
//

#ifndef CROMIO_IR_H
#define CROMIO_IR_H

#include <ast/nodes/nodes.h>
#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace cromio::lowering {
    class IR {
       public:
        explicit IR(const std::string& moduleName);

        // Generate module from AST
        llvm::Module* generate(const visitor::nodes::ProgramNode& node);

       private:
        // Core LLVM pieces
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        // Symbol table: variable name -> alloca
        std::unordered_map<std::string, llvm::AllocaInst*> symbols;

        // Helpers
        llvm::Type* mapDataType(const std::string& typeName) const;
        llvm::Value* promoteToDouble(llvm::Value* v) const;
        llvm::Type* inferType(const std::any& node) const;

        // Codegen utilities
        static llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, llvm::Type* type, const std::string& name);
        static std::unique_ptr<llvm::Module> loadBitcode(const std::string& path, llvm::LLVMContext& context);

        // Codegen for different node types
        llvm::Value* literal(const std::any& node);
        llvm::Value* expression(const std::any& node);
        llvm::Value* variableDeclaration(const visitor::nodes::VariableDeclarationNode& node);
        llvm::Value* variableAssignment(const visitor::nodes::VariableDeclarationNode& node);
        llvm::Value* arrayDeclaration(const visitor::nodes::ArrayDeclarationNode& node);
        llvm::Value* program(const visitor::nodes::ProgramNode& node);
        llvm::Value* statement(const visitor::nodes::StatementNode& node);

        void loadAndLinkModulesFromFolder() const;
        bool linkModule(std::unique_ptr<llvm::Module> other) const;
    };
} // namespace cromio::lowering

#endif // CROMIO_IR_H