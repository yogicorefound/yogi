//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <utils/wrapper/wrapper.h>

#include <cmath>
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("Binary expression evaluation", "[BINARY_EXPRESSION]") {
        // List of test expressions: { input_text, expected_value, expected_result_type, top_operator }
        auto test_cases = GENERATE(
            std::make_tuple<std::string>("1 + 1", 2.0, "int"),
            std::make_tuple<std::string>("10 * 2", 20.0, "int"),
            std::make_tuple<std::string>("10 / 3", 3.33, "float"),
            std::make_tuple<std::string>("5 - 2", 3.0, "int"),
            std::make_tuple<std::string>("(2 + 3) * 4", 20.0, "int"),
            std::make_tuple<std::string>("3 + 4 * 2 / (1 - 5)", 1.0, "float"),
            std::make_tuple<std::string>("((1 + 2) * (3 + 4))", 21.0, "int")

        );

        auto [text, expected_value, expected_type] = test_cases;
        const auto ast = Yogi::testAST(text);
        const auto& expression = utils::Helpers::resolveItem(ast.body[0]);
        const double value = std::round(std::stod(expression.value) * 100.0) / 100.0;

        // // Top-level checks
        REQUIRE(expression.type == expected_type);
        REQUIRE(value == expected_value);
    }
} // namespace yogi::visitor::nodes
