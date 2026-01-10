//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <utils/wrapper/wrapper.h>

#include <cmath>
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("Bitwise evaluation") {
        auto test_cases = GENERATE(
            std::make_tuple<std::string>("1 & 3", "1", "int"),
            std::make_tuple<std::string>("7 | 3", "7", "int"),
            std::make_tuple<std::string>("7 ^ 3", "4", "int"),
            std::make_tuple<std::string>("~20", "-21", "int"),
            std::make_tuple<std::string>("15 >> 1", "7", "int"),
            std::make_tuple<std::string>("15 << 1", "30", "int")

        );

        auto [text, expected_value, expected_type] = test_cases;
        const auto ast = Yogi::testAST(text);
        const auto& expression = utils::Helpers::resolveItem(ast.body[0]);

        REQUIRE(expression.type == expected_type);
        REQUIRE(expression.value == expected_value);
    }
} // namespace yogi::visitor::nodes
