//
// Created by Brayhan De Aza on 12/2/25.
//

#include "Scope.h"

namespace yogi::semantic {
    bool Scope::declareVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info) {
        if (symbols.contains(name))
            return false;

        // Store a shared_ptr of the node directly
        auto node_ptr = std::make_shared<visitor::nodes::VariableDeclarationNode>(info);
        symbols[name] = ScopeNode{
            visitor::nodes::Kind::VARIABLE_DECLARATION,
            std::make_shared<std::any>(node_ptr) // store shared_ptr<VariableDeclarationNode> in std::any
        };

        return true;
    }

    bool Scope::declareArray(const std::string& name, const visitor::nodes::ArrayDeclarationNode& info) {
        if (symbols.contains(name))
            return false;

        // Store a shared_ptr copy of the node
        symbols[name] = ScopeNode{visitor::nodes::Kind::ARRAY_DECLARATION, std::make_shared<std::any>(info)};
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
            symbols[name] = ScopeNode{visitor::nodes::Kind::VARIABLE_DECLARATION, std::make_shared<std::any>(info)};
            return;
        }

        // Otherwise try to update in parent scope
        if (parent) {
            parent->updateVariable(name, info);
        }
    }

    void Scope::updateArray(const std::string& name, const visitor::nodes::ArrayDeclarationNode& info) {
        // Update in current scope if it exists
        if (symbols.contains(name)) {
            symbols[name] = ScopeNode{visitor::nodes::Kind::ARRAY_DECLARATION, std::make_shared<std::any>(info)};
            return;
        }

        // Otherwise try to update in parent scope
        if (parent) {
            parent->updateArray(name, info);
        }
    }

    std::optional<std::shared_ptr<visitor::nodes::VariableDeclarationNode>> Scope::lookupVariable(const std::string& name) const {
        // Check current scope
        if (symbols.contains(name)) {
            const auto [kind, value] = symbols.at(name);

            if (kind != visitor::nodes::Kind::VARIABLE_DECLARATION) {
                return nullptr;
            }

            const auto node = std::any_cast<std::shared_ptr<visitor::nodes::VariableDeclarationNode>>(*value);
            return node;
        }

        // Check parent scopes recursively
        if (parent)
            return parent->lookupVariable(name);

        return std::nullopt;
    }

    std::optional<std::shared_ptr<visitor::nodes::ArrayDeclarationNode>> Scope::lookupArray(const std::string& name) const {
        // Check current scope

        if (symbols.contains(name)) {
            const auto [kind, value] = symbols.at(name);
            if (kind != visitor::nodes::Kind::ARRAY_DECLARATION) {
                return std::nullopt;
            }

            return std::any_cast<std::shared_ptr<visitor::nodes::ArrayDeclarationNode>>(value);
        }

        // Check parent scopes recursively
        if (parent)
            return parent->lookupArray(name);

        return std::nullopt;
    }

} // namespace yogi::semantic