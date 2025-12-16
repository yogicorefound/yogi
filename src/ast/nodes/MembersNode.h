//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace cromio::visitor::nodes {

    struct MemberExpressionNode : BaseNode {
        std::any object; // expresión base
        std::string member; // property o method
        std::vector<std::any> arguments; // vacío si es property
        bool isCall; // true = method call

        MemberExpressionNode(std::any object, std::string member, std::vector<std::any> arguments, bool isCall, Position start, Position end) : BaseNode(isCall ? Kind::MEMBER_METHOD : Kind::MEMBER_ACCESS, start, end), object(std::move(object)), member(std::move(member)), arguments(std::move(arguments)), isCall(isCall) {}
    };

} // namespace cromio::visitor::nodes