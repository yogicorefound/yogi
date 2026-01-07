//
// Created by Brayhan De Aza on 11/27/25.
//

#include "BaseVisitor.h"

namespace yogi::visitor {
    void BaseVisitor::enterScope() {
        const auto child = new semantic::Scope(scope);
        scope = child;
    }

    void BaseVisitor::exitScope() {
        if (scope->getParent() != nullptr) {
            scope = scope->getParent();
        }
    }

    semantic::Scope* BaseVisitor::getCurrentScope() const {
        return scope;
    }
} // namespace yogi::visitor