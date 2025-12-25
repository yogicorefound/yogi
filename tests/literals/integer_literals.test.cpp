//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

using namespace yogi::visitor::nodes;

TEST_CASE("Integer literal evaluation", "[INTEGER_LITERAL]") {
    const auto int_cases = GENERATE(
        std::make_tuple("0", "0"),
        std::make_tuple("1", "1"),
        std::make_tuple("-11", "-11"),
        std::make_tuple("42", "42"));

    const auto [c, expected_value] = int_cases;
    std::string text = c;

    const auto ast = yogi::Yogi::testAST(text);
    const auto& node = std::any_cast<IntegerLiteralNode>(ast.body[0].children.at(0));

    INFO("Integer value");
    REQUIRE(node.value == expected_value);

    INFO("Kind");
    REQUIRE(node.kind == Kind::INTEGER_LITERAL);

    INFO("Value parses to int");
    REQUIRE(std::stoi(node.value) == std::stoi(expected_value));
}
