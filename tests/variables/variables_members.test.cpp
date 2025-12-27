//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    const std::string testString = "hello, world!";

    const auto index = testString.find("world");
    auto findIndex = index != std::string::npos ? std::to_string(index) : "-1";
    TEST_CASE("Variables evaluation", "[MEMBER]") {
        // List of test expressions: { input_text, expected_value, expected_result_type, top_operator }
        auto cases = GENERATE(
            // string members
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.size()", std::to_string(testString.size()), "int"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.lower()", utils::Helpers::toLower(testString), "str"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.upper()", utils::Helpers::toUpper(testString), "str"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.title()", utils::Helpers::toTitle(testString), "str"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.includes(\"world\")", testString.contains("world") ? "1" : "0", "bool"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.startWith(\"world\")", testString.starts_with("world") ? "1" : "0", "bool"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.endsWith(\"world\")", testString.ends_with("world") ? "1" : "0", "bool"),
            std::make_tuple<std::string, std::string>("str a = \"" + testString + "\" a.find(\"world\")", std::move(findIndex), "int")

        );

        auto [text, expectedValue, expectedType] = cases;
        const auto ast = Yogi::testAST(text);
        const auto [type, value, node] = utils::Helpers::resolveItem(ast.body[1].children.at(0));

        REQUIRE(value == expectedValue);
        REQUIRE(type == expectedType);
    }
} // namespace yogi::visitor::nodes
