//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("Variables evaluation", "[MEMBER]") {
        // List of test expressions: { input_text, expected_value, expected_result_type, top_operator }
        auto cases = GENERATE(
            // string members
            std::make_tuple<std::string, std::string>("str a = \"yx\" a.size", "2", "int")

        );

        auto [text, expectedValue, expectedType] = cases;
        const auto ast = Yogi::testAST(text);
        const auto [type, value, node] = utils::Helpers::resolveItem(ast.body[1].children.at(0));

        REQUIRE(value == expectedValue);
        REQUIRE(type == expectedType);
    }
} // namespace yogi::visitor::nodes
