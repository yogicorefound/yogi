//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include "../../src/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    constexpr std::string testString = "hello, world!";
    constexpr auto index = testString.find("world");

    auto findIndex = index != std::string::npos ? std::to_string(index) : "-1";
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,})");

    TEST_CASE("Variables evaluation", "[MEMBER]") {
        auto cases = GENERATE(
            // TODO: "split", "match",  "unicode",

            // Done
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.reverse()", utils::Helpers::reverse(testString), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.slice(0, 5)", utils::Helpers::slice(testString, 0, 5), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.at(1).repeat(2)", utils::Helpers::repeat(utils::Helpers::at(testString, 1), 2), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.at(0)", std::string(1, testString.at(0)), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.size()", std::to_string(testString.size()), "int"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.lower()", utils::Helpers::toLower(testString), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.upper()", utils::Helpers::toUpper(testString), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.title()", utils::Helpers::toTitle(testString), "str"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.includes(\"world\")", testString.contains("world") ? "1" : "0", "bool"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.startWith(\"world\")", testString.starts_with("world") ? "1" : "0", "bool"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.endsWith(\"world\")", testString.ends_with("world") ? "1" : "0", "bool"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.find(\"world\")", std::move(findIndex), "int"),
            std::make_tuple<std::string>("str a = \"" + testString + "\" a.replace(\"world\", \"mundo\")", utils::Helpers::replace(testString, "world", "mundo"), "str")

        );

        auto [text, expectedValue, expectedType] = cases;
        const auto ast = Yogi::testAST(text);
        const auto memberNode = std::any_cast<MemberExpressionNode>(ast.body[1].children[0]);
        const auto [type, value, node] = utils::Helpers::resolveItem(memberNode.value);

        REQUIRE(value == expectedValue);
        REQUIRE(type == expectedType);
    }
} // namespace yogi::visitor::nodes
