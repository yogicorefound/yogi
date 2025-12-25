//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

using namespace yogi::visitor::nodes;

TEST_CASE("None evaluation", "[NONE_LITERAL]") {
    const auto bool_cases = GENERATE(std::make_tuple("none", "none"));
    const auto [c, expected_value] = bool_cases;

    std::string text = c;
    const auto ast = yogi::Yogi::testAST(text);
    const auto& node = std::any_cast<NoneLiteralNode>(ast.body[0].children.at(0));

    INFO("None kind");
    REQUIRE(node.kind == Kind::NONE_LITERAL);

    INFO("None value");
    REQUIRE(node.value == expected_value);
}
