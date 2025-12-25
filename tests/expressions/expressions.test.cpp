//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("Binary expression evaluation", "[BINARY_EXPRESSION]") {
        // List of test expressions: { input_text, expected_value, expected_result_type, top_operator }
        auto test_cases = GENERATE(
            std::make_tuple("1 + 1", 2.0, "int", "+"),
            std::make_tuple("10 * 2", 20.0, "int", "*"),
            std::make_tuple("10 / 3", 3.33, "float", "/"),
            std::make_tuple("5 - 2", 3.0, "int", "-"),
            std::make_tuple("(2 + 3) * 4", 20.0, "int", "*"),
            std::make_tuple("3 + 4 * 2 / (1 - 5)", 1.0, "float", "+"),
            std::make_tuple("((1 + 2) * (3 + 4))", 21.0, "int", "*") //
        );

        const auto [text, expected_value, expected_type, expected_op] = test_cases;

        INFO("Testing expression: " << text);

        std::string ctx = text;
        const auto ast = Yogi::testAST(ctx);
        const auto& expression = std::any_cast<BinaryExpressionNode>(ast.body[0].children.at(0));

        // Top-level checks
        REQUIRE(expression.kind == Kind::BINARY_EXPRESSION);
        REQUIRE(expression.op == expected_op);
        REQUIRE(expression.resultType == expected_type);

        // Left operand
        const auto [lType, lValue, lNode] = utils::Helpers::resolveItem(expression.left);
        INFO("Left operand: " << lValue);
        REQUIRE(!lValue.empty());

        // Right operand
        const auto [rType, rValue, rNode] = utils::Helpers::resolveItem(expression.right);
        INFO("Right operand: " << rValue);
        REQUIRE(!rValue.empty());

        // Evaluate and round to 2 decimals
        double rounded = std::round(std::stod(expression.value) * 100.0) / 100.0;
        REQUIRE(rounded == Catch::Approx(expected_value).epsilon(0.01));
    }
} // namespace yogi::visitor::nodes
