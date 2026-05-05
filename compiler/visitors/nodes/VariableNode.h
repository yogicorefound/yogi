//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <utility>

#include "BaseNode.h"
#include "utils/utils.h"
#include "utils/types/Types.h"

namespace yogi::visitor::nodes {
    // Variable Declaration Statement
    struct VariableDeclarationNode : BaseNode {
        std::string identifier; // Variable name
        utils::Types varType; // Type: "int", "float", "str", "bool", etc.
        std::any value; // Initial value (can be any literal or expression node)

        bool isConstant; // true for 'const', false for 'var'

        explicit VariableDeclarationNode(std::string  identifier, const utils::Types  type, std::any value, const bool isConstant, const Position start, const Position end): BaseNode(Kind::VARIABLE_DECLARATION, start, end),
            identifier(std::move(identifier)),
            varType(type),
            value(std::move(value)),
            isConstant(isConstant) {
        }
    };

} // namespace yogi::visitor::nodes
