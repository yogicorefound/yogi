//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <vector>
#include "BaseNode.h"
#include <regex>

namespace yogi::visitor::nodes {

    // Integer Literal
    struct IntegerLiteralNode : BaseNode {
        std::string value;

        explicit IntegerLiteralNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::INTEGER_LITERAL, start, end), value(v) {}
    };

    // Float Literal
    struct FloatLiteralNode : BaseNode {
        std::string value;
        explicit FloatLiteralNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::FLOAT_LITERAL, start, end), value(v) {}
    };

    // Identifier Literal
    struct IdentifierLiteral : BaseNode {
        std::string value;
        explicit IdentifierLiteral(const std::string& v, const Position start, const Position end) : BaseNode(Kind::IDENTIFIER_LITERAL, start, end), value(v) {}
    };

    // Boolean Literal
    struct BooleanLiteralNode : BaseNode {
        std::string value;

        explicit BooleanLiteralNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::BOOLEAN_LITERAL, start, end), value(v) {}
    };

    // None Literal
    struct NoneLiteralNode : BaseNode {
        std::string value;

        explicit NoneLiteralNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::NONE_LITERAL, start, end), value(v) {}
    };

    // String Literal
    struct StringLiteralNode : BaseNode {
        std::string value;

        explicit StringLiteralNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::STRING_LITERAL, start, end), value(v) {}
    };

    // String Literal
    struct RegexLiteralNode : BaseNode {
        std::string value;
        explicit RegexLiteralNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::STRING_LITERAL, start, end), value(v) {}
    };

    // Formatted String Literal
    struct FormattedStringNode : BaseNode {
        std::string value;
        std::vector<BaseNode> params;

        explicit FormattedStringNode(const std::string& v, const Position start, const Position end) : BaseNode(Kind::FORMATTED_STRING, start, end), value(v) {}
    };

} // namespace yogi::visitor::nodes
