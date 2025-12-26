//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <bitset>
#include <random>
#include <sstream>
#include <string>
#include "includes/yogi/yogi.h"
#include "libs/catch2/catch_amalgamated.hpp"

namespace yogi::visitor::nodes {
    TEST_CASE("arrays evaluation", "[ARRAY]", ) {
        const auto cases = GENERATE(
            // ===== int8 scenarios =====
            std::make_tuple<std::string, std::string, std::string>("int8[] a = [0, -1, 1, 2]", "int8", "a", "auto", std::vector{0, -1, 1, 2}),
            std::make_tuple<std::string, std::string, std::string>("int8[3] a = [-5, 0, 5]", "int8", "a", "3", std::vector{-5, 0, 5}),
            std::make_tuple<std::string, std::string, std::string>("int8[2] a = [10, -10]", "int8", "a", "2", std::vector{10, -10}),

            // ===== int16 scenarios =====
            std::make_tuple<std::string, std::string, std::string>("int16[] a = [100, 200, -300]", "int16", "a", "auto", std::vector{100, 200, -300}),
            std::make_tuple<std::string, std::string, std::string>("int16[4] a = [0, 1, 2, 3]", "int16", "a", "4", std::vector{0, 1, 2, 3}),
            std::make_tuple<std::string, std::string, std::string>("int16[2] a = [-1000, 1000]", "int16", "a", "2", std::vector{-1000, 1000}),

            // ===== int32 scenarios =====
            std::make_tuple("int32[] a = [100000, -100000]", "int32", "a", "auto", std::vector{100000, -100000}),
            std::make_tuple("int32[3] a = [1, 10, 100]", "int32", "a", "3", std::vector{1, 10, 100}),
            std::make_tuple("int32[1] a = [0]", "int32", "a", "1", std::vector{0}),

            // ===== int64 scenarios =====
            std::make_tuple("int64[] a = [1000000000, -1000000000]", "int64", "a", "auto", std::vector{1000000000, -1000000000}),
            std::make_tuple("int64[3] a = [1, 2, 3]", "int64", "a", "3", std::vector{1, 2, 3}),
            std::make_tuple("int64[2] a = [9223372, -9223372]", "int64", "a", "2", std::vector{9223372, -9223372})

        );

        auto [text, type, name, size, expectedItems] = cases;
        const auto ast = Yogi::testAST(text);
        const auto& node = std::any_cast<ArrayDeclarationNode>(ast.body[0].children.at(0));

        REQUIRE(node.kind == Kind::ARRAY_DECLARATION);
        REQUIRE(node.type == type);
        REQUIRE(node.identifier == name);
        REQUIRE(node.size == size);

        for (int i = 0; i < node.elements.size(); i++) {
            const auto item = node.elements[i];
            const auto expectedValue = expectedItems[i];
            const auto [resolvedItemType, resolvedItemValue, resolvedItemNode] = utils::Helpers::resolveItem(item.value);

            REQUIRE(resolvedItemValue == std::to_string(expectedValue));
            REQUIRE(item.type == resolvedItemType);
            REQUIRE(resolvedItemNode.type() == item.value.type());
        }
    }

} // namespace yogi::visitor::nodes