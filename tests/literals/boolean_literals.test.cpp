//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

using namespace yogi::visitor::nodes;

TEST_CASE("Boolean evaluation", "[BOOLEAN_LITERAL]") {
    const auto bool_cases = GENERATE(std::make_tuple("true", true), std::make_tuple("false", false));

    const auto [c, expected_value] = bool_cases;
    std::string text = c;

    const auto ast = yogi::Yogi::testAST(text);
    const auto& node = std::any_cast<BooleanLiteralNode>(ast.body[0].children.at(0));

    INFO("Boolean kind");
    REQUIRE(node.kind == Kind::BOOLEAN_LITERAL);

    INFO("Boolean value");
    REQUIRE(node.value == (expected_value ? "1" : "0"));
}
