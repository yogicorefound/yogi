//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <utils/wrapper/wrapper.h>
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("Condition evaluation") {
        auto cases = GENERATE(
            std::make_tuple<std::string>("!(5 > 0) ? true : false", "0", "bool"),
            std::make_tuple<std::string>("!1 ? true : false", "0", "bool"),
            std::make_tuple<std::string>("!0 ? true : false", "1", "bool"),

            std::make_tuple<std::string>("(5 == 5) ? true : false", "1", "bool"),
            std::make_tuple<std::string>("5 == 5 ? true : false", "1", "bool"),
            std::make_tuple<std::string>("3 >= 3 ? true : false", "1", "bool"),
            std::make_tuple<std::string>("3 <= 2 ? true : false", "0", "bool"),

            std::make_tuple<std::string>("3 != 2 ? true : false", "1", "bool"),

            std::make_tuple<std::string>("5 > 0 ? true : false", "1", "bool"),
            std::make_tuple<std::string>("5 < 0 ? true : false", "0", "bool"),
            std::make_tuple<std::string>("(5 > 0) ? true : false", "1", "bool")

        );

        auto [text, expectedValue, expectedType] = cases;
        const auto ast = Yogi::testAST(text);
        const auto [type, value, node] = utils::Helpers::resolveItem(ast.body[0]);

        REQUIRE(value == expectedValue);
        REQUIRE(type == expectedType);
    }
} // namespace yogi::visitor::nodes
