//
// Created by Brayhan De Aza on 11/27/25.
//

#include "BaseVisitor.h"

void cromio::visitor::BaseVisitor::enterScope() {
    const auto child = new semantic::Scope(scope);
    scope = child;
}

void cromio::visitor::BaseVisitor::exitScope() {
    if (scope->getParent() != nullptr) {
        scope = scope->getParent();
    }
}

cromio::semantic::Scope* cromio::visitor::BaseVisitor::getCurrentScope() const {
    return scope;
}