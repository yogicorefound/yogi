//
// Created by Brayhan De Aza on 12/2/25.
//

#include "Scope.h"

namespace cromio::semantic {
    bool Scope::declareVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info) {
        if (symbols.contains(name))
            return false;

        // Store a shared_ptr copy of the node
        symbols[name] = std::make_shared<visitor::nodes::VariableDeclarationNode>(info);
        return true;
    }
    bool Scope::declareArray(const std::string& name, const visitor::nodes::ArrayDeclarationNode& info) {
        if (arraySymbols.contains(name))
            return false;

        // Store a shared_ptr copy of the node
        arraySymbols[name] = std::make_shared<visitor::nodes::ArrayDeclarationNode>(info);
        return true;
    }

    bool Scope::exists(const std::string& name) const {
        // Check current scope
        if (symbols.contains(name))
            return true;

        // Check parent scopes recursively
        if (parent)
            return parent->exists(name);

        return false;
    }

    bool Scope::existsInCurrent(const std::string& name) const {
        return symbols.contains(name);
    }

    void Scope::updateVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info) {
        // Update in current scope if it exists
        if (symbols.contains(name)) {
            symbols[name] = std::make_shared<visitor::nodes::VariableDeclarationNode>(info);
            return;
        }

        // Otherwise try to update in parent scope
        if (parent) {
            parent->updateVariable(name, info);
        }
    }

    void Scope::updateArray(const std::string& name, const visitor::nodes::ArrayDeclarationNode& info) {
        // Update in current scope if it exists
        if (arraySymbols.contains(name)) {
            arraySymbols[name] = std::make_shared<visitor::nodes::ArrayDeclarationNode>(info);
            return;
        }

        // Otherwise try to update in parent scope
        if (parent) {
            parent->updateArray(name, info);
        }
    }

    std::optional<std::shared_ptr<visitor::nodes::VariableDeclarationNode>> Scope::lookup(const std::string& name) const {
        // Check current scope
        if (symbols.contains(name))
            return symbols.at(name);

        // Check parent scopes recursively
        if (parent)
            return parent->lookup(name);

        return std::nullopt;
    }

    std::optional<std::shared_ptr<visitor::nodes::ArrayDeclarationNode>> Scope::lookupArray(const std::string& name) const {
        // Check current scope
        if (arraySymbols.contains(name))
            return arraySymbols.at(name);

        // Check parent scopes recursively
        if (parent)
            return parent->lookupArray(name);

        return std::nullopt;
    }

} // namespace cromio::semantic