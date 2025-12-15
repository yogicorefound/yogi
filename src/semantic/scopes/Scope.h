//
// Created by Brayhan De Aza on 12/2/25.
//

#ifndef CROMIO_SCOPE_H
#define CROMIO_SCOPE_H

#include <ast/nodes/nodes.h>
#include <utils/utils.h>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include "semantic/BaseSemantic.h"

namespace cromio::semantic {
    class Scope : public virtual BaseSemantic {
       public:
        explicit Scope(Scope* parent = nullptr) : parent(parent) {}

        // variables
        bool declareVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info);
        void updateVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info);
        std::optional<std::shared_ptr<visitor::nodes::VariableDeclarationNode>> lookup(const std::string& name) const;

        // arrays
        bool declareArray(const std::string& name, const visitor::nodes::ArrayDeclarationNode& info);
        void updateArray(const std::string& name, const visitor::nodes::ArrayDeclarationNode& info);
        std::optional<std::shared_ptr<visitor::nodes::ArrayDeclarationNode>> lookupArray(const std::string& name) const;

        bool exists(const std::string& name) const;
        bool existsInCurrent(const std::string& name) const;


        // Create a child scope
        Scope* createChild() {
            return new Scope(this);
        }

        Scope* getParent() const {
            return parent;
        }

       private:
        Scope* parent;
        std::unordered_map<std::string, std::shared_ptr<visitor::nodes::VariableDeclarationNode>> symbols = {};
        std::unordered_map<std::string, std::shared_ptr<visitor::nodes::ArrayDeclarationNode>> arraySymbols = {};
    };

} // namespace cromio::semantic

#endif // CROMIO_SCOPE_H