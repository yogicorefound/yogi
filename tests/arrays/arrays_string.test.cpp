//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <bitset>
#include <random>
#include <string>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("arrays evaluation", "[string]", ) {
        const auto cases = GENERATE(
            // ===== str literal scenarios =====
            std::make_tuple<std::string>("str[] a = [\"hello\", \"world\"]", "str", "a", "auto", std::vector<std::string>{"hello", "world"}, false),
            std::make_tuple("str[1] a = [\"single\"]", "str", "a", "1", std::vector<std::string>{"single"}, false),
            std::make_tuple("str[3] a = [\"a\", \"b\", \"c\"]", "str", "a", "3", std::vector<std::string>{"a", "b", "c"}, false),
            std::make_tuple("str[2] a = [\"\", \"empty\"]", "str", "a", "2", std::vector<std::string>{"", "empty"}, false),

            // ===== str concatenation scenarios =====
            std::make_tuple("str[] a = [\"hello\" + \" \" + \"world\"]", "str", "a", "auto", std::vector<std::string>{"hello world"}, false),
            std::make_tuple("str[1] a = [\"foo\" + \"bar\"]", "str", "a", "1", std::vector<std::string>{"foobar"}, false),
            std::make_tuple("str[2] a = [\"a\" + \"b\", \"c\" + \"d\"]", "str", "a", "2", std::vector<std::string>{"ab", "cd"}, false),
            std::make_tuple("str[3] a = [\"x\", \"y\" + \"z\", \"\"]", "str", "a", "3", std::vector<std::string>{"x", "yz", ""}, false),

            // ===== str concatenation scenarios =====
            std::make_tuple("str a = \"x\" str[] b = [a]", "str", "b", "auto", std::vector<std::string>{"x"}, true),
            std::make_tuple("str a = \"x\" str[] b = [a + \"y\"]", "str", "b", "auto", std::vector<std::string>{"xy"}, true),
            std::make_tuple("str a = \"x\" str[] b = [a + a]", "str", "b", "auto", std::vector<std::string>{"xx"}, true)

        );

        auto [text, type, name, size, expectedItems, isMuliLine] = cases;
        const auto ast = Yogi::testAST(text);
        const auto& node = std::any_cast<ArrayDeclarationNode>(ast.body[isMuliLine ? 1 : 0].children.at(0));

        REQUIRE(node.kind == Kind::ARRAY_DECLARATION);
        REQUIRE(node.type == type);
        REQUIRE(node.identifier == name);
        REQUIRE(node.size == size);

        // for (int i = 0; i < node.elements.size(); i++) {
        //     const auto item = node.elements[i];
        //     const auto expectedValue = expectedItems[i];
        //     const auto [resolvedItemType, resolvedItemValue, resolvedItemNode] = utils::Helpers::resolveItem(item.value);
        //
        //     REQUIRE(resolvedItemValue == expectedValue);
        //     REQUIRE(item.type == resolvedItemType);
        //     REQUIRE(resolvedItemNode.type() == item.value.type());
        // }
    }

} // namespace yogi::visitor::nodes