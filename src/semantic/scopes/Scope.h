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

        bool declareVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info);
        bool exists(const std::string& name) const;
        bool existsInCurrent(const std::string& name) const;
        void updateVariable(const std::string& name, const visitor::nodes::VariableDeclarationNode& info);

        std::optional<std::shared_ptr<visitor::nodes::VariableDeclarationNode>> lookup(const std::string& name) const;

        // Create a child scope
        Scope* createChild() {
            return new Scope(this);
        }

        Scope* getParent() const {
            return parent;
        }

       private:
        Scope* parent;
        // Use shared_ptr to avoid copy issues with std::any
        std::unordered_map<std::string, std::shared_ptr<visitor::nodes::VariableDeclarationNode>> symbols;
    };

} // namespace cromio::semantic

#endif // CROMIO_SCOPE_H