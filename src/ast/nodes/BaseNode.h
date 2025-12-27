//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <cstddef>

namespace yogi::visitor::nodes {

    enum class Kind {
        PROGRAM,
        STATEMENT,
        DATA_TYPE,

        // Regex
        REGEX_LITERAL,

        // Literal
        INTEGER_LITERAL,
        FLOAT_LITERAL,
        BOOLEAN_LITERAL,
        NONE_LITERAL,
        IDENTIFIER_LITERAL,
        STRING_LITERAL,
        FORMATTED_STRING,
        UNKNOWN_LITERAL,

        // Expression
        BINARY_EXPRESSION,
        CONCATENATION_EXPRESSION,

        // Members
        MEMBER_NODE,
        MEMBER_METHOD,
        MEMBER_PROPERTY,
        MEMBER_ACCESS,
        MEMBER_ELEMENT,

        // Statement
        VARIABLE_DECLARATION,

        ARRAY_DECLARATION,
        ARRAY_ELEMENT,
        ARRAY_ELEMENTS,

        DICTIONARY_DECLARATION,
        DICTIONARY_PAIR,
        DICTIONARY_TYPE,

        BLOCK,

    };

    struct Position {
        size_t line;
        size_t column;
    };

    struct BaseNode {
        Kind kind;
        Position start;
        Position end;

        explicit BaseNode(const Kind k, const Position s, const Position e) : kind(k), start(s), end(e) {
            kind = k;
            start = s;
            end = e;
        }
    };

} // namespace yogi::visitor::nodes
