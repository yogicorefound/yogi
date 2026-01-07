//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace yogi::visitor::nodes {

    struct MemberExpressionNode : BaseNode {
        std::any value; // expresión base
        Kind kind; // property o method

        MemberExpressionNode(const std::any& value, const Kind kind, Position const start, const Position end) : BaseNode(kind, start, end), value(value), kind(kind) {}
    };

} // namespace yogi::visitor::nodes