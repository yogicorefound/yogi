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
    TEST_CASE("arrays evaluation", "[int8]", ) {
        const auto cases = GENERATE(
            // ===== int8 scenarios =====
            std::make_tuple<std::string>("int8[] a = [0, -1, 1, 12]", "int8", "a", "auto", std::vector{0, -1, 1, 12}),
            std::make_tuple<std::string>("int8[3] a = [-12, 0, 12]", "int8", "a", "3", std::vector{-12, 0, 12}),
            std::make_tuple<std::string>("int8[4] a = [1, 2, 4, 8]", "int8", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple<std::string>("int8[2] a = [-64, 64]", "int8", "a", "2", std::vector{-64, 64}),

            // ===== uint8 scenarios =====
            std::make_tuple<std::string>("uint8[] a = [0, 1, 10, 25]", "uint8", "a", "auto", std::vector{0, 1, 10, 25}),
            std::make_tuple<std::string>("uint8[3] a = [0, 15, 30]", "uint8", "a", "3", std::vector{0, 15, 30}),
            std::make_tuple<std::string>("uint8[4] a = [1, 2, 4, 8]", "uint8", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple<std::string>("uint8[2] a = [64, 127]", "uint8", "a", "2", std::vector{64, 127}),

            // ===== int16 scenarios =====
            std::make_tuple<std::string>("int16[] a = [0, -10, 10, 320]", "int16", "a", "auto", std::vector{0, -10, 10, 320}),
            std::make_tuple<std::string>("int16[3] a = [-327, 0, 327]", "int16", "a", "3", std::vector{-327, 0, 327}),
            std::make_tuple<std::string>("int16[4] a = [1, 2, 4, 8]", "int16", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple<std::string>("int16[2] a = [-1024, 1024]", "int16", "a", "2", std::vector{-1024, 1024}),

            // ===== uint16 scenarios =====
            std::make_tuple<std::string>("uint16[] a = [0, 1, 10, 655]", "uint16", "a", "auto", std::vector{0, 1, 10, 655}),
            std::make_tuple<std::string>("uint16[3] a = [0, 100, 1000]", "uint16", "a", "3", std::vector{0, 100, 1000}),
            std::make_tuple<std::string>("uint16[4] a = [1, 2, 4, 8]", "uint16", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple<std::string>("uint16[2] a = [1024, 2048]", "uint16", "a", "2", std::vector{1024, 2048}),

            // ===== int32 scenarios =====
            std::make_tuple("int32[] a = [0, -100, 100, 1000]", "int32", "a", "auto", std::vector{0, -100, 100, 1000}),
            std::make_tuple("int32[3] a = [-1000, 0, 1000]", "int32", "a", "3", std::vector{-1000, 0, 1000}),
            std::make_tuple("int32[4] a = [1, 2, 4, 8]", "int32", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple("int32[2] a = [-100000, 100000]", "int32", "a", "2", std::vector{-100000, 100000}),

            // ===== uint32 scenarios =====
            std::make_tuple("uint32[] a = [0, 1, 100, 1000]", "uint32", "a", "auto", std::vector{0, 1, 100, 1000}),
            std::make_tuple("uint32[3] a = [0, 1000, 100000]", "uint32", "a", "3", std::vector{0, 1000, 100000}),
            std::make_tuple("uint32[4] a = [1, 2, 4, 8]", "uint32", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple("uint32[2] a = [1000000, 2000000]", "uint32", "a", "2", std::vector{1000000, 2000000}),

            // ===== int64 scenarios =====
            std::make_tuple("int64[] a = [0, -1000000, 1000000, 10000000]", "int64", "a", "auto", std::vector{0, -1000000, 1000000, 10000000}),
            std::make_tuple("int64[3] a = [-10000000, 0, 10000000]", "int64", "a", "3", std::vector{-10000000, 0, 10000000}),
            std::make_tuple("int64[4] a = [1, 2, 4, 8]", "int64", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple("int64[2] a = [-1000000000, 1000000000]", "int64", "a", "2", std::vector{-1000000000, 1000000000}),

            // ===== uint64 scenarios =====
            std::make_tuple("uint64[] a = [0, 1, 1000000, 10000000]", "uint64", "a", "auto", std::vector{0, 1, 1000000, 10000000}),
            std::make_tuple("uint64[3] a = [0, 10000000, 100000000]", "uint64", "a", "3", std::vector{0, 10000000, 100000000}),
            std::make_tuple("uint64[4] a = [1, 2, 4, 8]", "uint64", "a", "4", std::vector{1, 2, 4, 8}),
            std::make_tuple("uint64[2] a = [1000000000, 2000000000]", "uint64", "a", "2", std::vector{1000000000, 2000000000})

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