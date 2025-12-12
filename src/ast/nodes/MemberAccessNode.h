//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace cromio::visitor::nodes {
    // Member Access (e.g., object.property)
    struct MemberAccessNode : BaseNode {
        std::string object;      // Object/variable name
        std::string member;      // Member/property name

        explicit MemberAccessNode(
            const std::string& obj,
            const std::string& mem,
            const Position start,
            const Position end
        ) : BaseNode(Kind::MEMBER_ACCESS, start, end),
            object(obj),
            member(mem) {}
    };

} // namespace cromio::visitor::nodes

