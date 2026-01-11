//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <utils/wrapper/wrapper.h>

#include <cmath>
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    // --------------------------------------------------------
    // Relational: >, <, >=, <=, ==, !=, !
    // --------------------------------------------------------
    TEST_CASE("Relational expression evaluation", "[RELATIONAL_EXPRESSION]") {
        auto test_cases = GENERATE(
            std::make_tuple<std::string>("+3.0 > 2", "1", "bool"),
            std::make_tuple<std::string>("+3.0 > 4", "0", "bool"),

            std::make_tuple<std::string>("+3.0 < 2", "0", "bool"),
            std::make_tuple<std::string>("+3.0 < 5", "1", "bool"),

            std::make_tuple<std::string>("+3.0 >= 3", "1", "bool"),
            std::make_tuple<std::string>("+3.0 >= 3", "1", "bool"),
            std::make_tuple<std::string>("+3.0 >= 6", "0", "bool"),

            std::make_tuple<std::string>("+3.0 <= 6", "1", "bool"),
            std::make_tuple<std::string>("+6.0 <= 6", "1", "bool"),
            std::make_tuple<std::string>("+6.0 <= 2", "0", "bool"),

            std::make_tuple<std::string>("10 == 9", "0", "bool"),
            std::make_tuple<std::string>("10 == 10", "1", "bool"),
            std::make_tuple<std::string>("10 == 10.0", "1", "bool"),

            std::make_tuple<std::string>("(10 * 10) != (10 * 10)", "0", "bool"),
            std::make_tuple<std::string>("10 != 9", "1", "bool"),

            std::make_tuple<std::string>("!!(10 * 10)", "1", "bool")

        );

        auto [text, expected_value, expected_type] = test_cases;
        const auto ast = Yogi::testAST(text);
        const auto& expression = utils::Helpers::resolveItem(ast.body[0]);

        // // Top-level checks
        REQUIRE(expression.type == expected_type);
        REQUIRE(expression.value == expected_value);
    }
} // namespace yogi::visitor::nodes
