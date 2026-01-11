//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <utils/wrapper/wrapper.h>
#include <visitors/nodes/ConditionsNode.h>
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("if Condition evaluation") {
        auto cases = GENERATE(
            std::make_tuple<std::string>("if(''){}","0","bool"),
            std::make_tuple<std::string>("if(' '){}","1","bool"),
            std::make_tuple<std::string>("if('Hello, World!!'){}", "1", "bool"),

            std::make_tuple<std::string>("if(!'Hello, World!!'){}", "0", "bool"),
            std::make_tuple<std::string>("if('a' != 'a'){}", "0", "bool"),

            std::make_tuple<std::string>("if(0 == 1){}", "0", "bool"),
            std::make_tuple<std::string>("if('a' == 'a'){}", "1", "bool"),

            std::make_tuple<std::string>("if(0 >= 1){}", "0", "bool"),
            std::make_tuple<std::string>("if('a' >= 'a'){}", "1", "bool"),
            std::make_tuple<std::string>("if('a' <= 'b'){}", "1", "bool"),
            std::make_tuple<std::string>("if('a' > 'a'){}", "0", "bool"),

            std::make_tuple<std::string>("if(1 << 0){}", "1", "bool"),
            std::make_tuple<std::string>("if(1 >> 0){}", "1", "bool"),

            std::make_tuple<std::string>("if(1 | 0){}", "1", "bool"),
            std::make_tuple<std::string>("if(0 | 0){}", "0", "bool"),

            std::make_tuple<std::string>("if(1 ^ 0){}", "1", "bool"),
            std::make_tuple<std::string>("if(0 ^ 0){}", "0", "bool")

        );

        auto [text, expectedValue, expectedType] = cases;
        const auto ast = Yogi::testAST(text);
        const auto ifStatementNode = std::any_cast<IfStatementNode>(ast.body[0]);
        const auto [type, value, node] = utils::Helpers::resolveItem(ifStatementNode.branches[0].condition);

        REQUIRE(value == expectedValue);
        REQUIRE(type == expectedType);
    }
} // namespace yogi::visitor::nodes
