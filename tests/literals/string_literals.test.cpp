//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("Literal evaluation", "[STRING_LITERAL]") {
        const auto string_cases = GENERATE(
            std::make_tuple("\"Hello, world!!\"", "Hello, world!!", Kind::STRING_LITERAL),
            std::make_tuple("\"firstName \" + \"lastName\"", "firstName lastName", Kind::STRING_LITERAL),
            std::make_tuple("\"a\" + \"b\" + \"c\"", "abc", Kind::STRING_LITERAL),
            std::make_tuple("\"Hello \" + \"(\" + \"World\" + \")\"", "Hello (World)", Kind::STRING_LITERAL),
            std::make_tuple("\"  leading and trailing  \"", "  leading and trailing  ", Kind::STRING_LITERAL),
            std::make_tuple("\"multi\\nline\"", "multi\nline", Kind::STRING_LITERAL),
            std::make_tuple("\"tab\\tcharacter\"", "tab\tcharacter", Kind::STRING_LITERAL));

        const auto [c, expected_value, expected_kind] = string_cases;
        std::string text = c;

        const auto ast = Yogi::testAST(text);
        const auto& node = std::any_cast<StringLiteralNode>(ast.body[0].children.at(0));

        INFO("String value");
        REQUIRE(node.value == expected_value);

        INFO("Kind");
        REQUIRE(node.kind == expected_kind);

        INFO("Start position");
        REQUIRE(typeid(node.start.line) == typeid(size_t));
        REQUIRE(typeid(node.start.column) == typeid(size_t));

        INFO("End position");
        REQUIRE(typeid(node.end.line) == typeid(size_t));
        REQUIRE(typeid(node.end.column) == typeid(size_t));
    }
} // namespace yogi::visitor::nodes