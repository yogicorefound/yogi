//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <cstddef>

namespace cromio::visitor::nodes {

    enum class Kind {
        PROGRAM,
        STATEMENT,
        DATA_TYPE,


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

        // Statement
        VARIABLE_DECLARATION,

        ARRAY_DECLARATION,
        ARRAY_ELEMENT,

        DICTIONARY_DECLARATION,
        DICTIONARY_PAIR,
        DICTIONARY_TYPE,

        BLOCK,
        MEMBER_ACCESS
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

} // namespace cromio::visitor::nodes
