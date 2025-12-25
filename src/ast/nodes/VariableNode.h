//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace yogi::visitor::nodes {
    // Variable Declaration Statement
    struct VariableDeclarationNode : BaseNode {
        std::string identifier; // Variable name
        std::string varType; // Type: "int", "float", "str", "bool", etc.
        std::any value; // Initial value (can be any literal or expression node)

        bool isConstant; // true for 'const', false for 'var'

        explicit VariableDeclarationNode(const std::string& identifier, const std::string& type, std::any value, const bool isConstant, const Position start, const Position end) : BaseNode(Kind::VARIABLE_DECLARATION, start, end), identifier(identifier), varType(type), value(std::move(value)), isConstant(isConstant) {
            ///
        }
    };

} // namespace yogi::visitor::nodes
