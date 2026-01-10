// //
// // Created by Brayhan De Aza on 12/12/25.
// //
//
// #include <utils/helpers/Helpers.h>
// #include <utils/wrapper/wrapper.h>
// #include <visitors/nodes/VariableNode.h>
// #include "libs/catch2/catch_amalgamated.hpp"
//
// namespace yogi::visitor::nodes {
//     constexpr std::string testString = "hello, world!";
//
//     TEST_CASE("Variables Re-Assignment evaluation", "[Re-Assignment]") {
//         auto cases = GENERATE(
//             // string members
//             std::make_tuple<std::string>("str x = \"" + testString + "\" x = \"brayhan\"", "brayhan", "str"),
//             std::make_tuple<std::string>("int x = 10 x = x + 10", "20", "int"),
//             std::make_tuple<std::string>("float x = 10.0 x = x + 10.0", "20.000000", "float"),
//             std::make_tuple<std::string>("bool x = true x = false", "0", "bool"),
//             std::make_tuple<std::string>("regex x = r\"/[0-9]/\" x = r\"/[A-Z]/\"", "/[A-Z]/", "regex")
//
//         );
//
//         auto [text, expectedValue, expectedType] = cases;
//         const auto ast = Yogi::testAST(text);
//
//         const auto memberNode = std::any_cast<VariableDeclarationNode>(ast.body[1]);
//         const auto [type, value, node] = utils::Helpers::resolveItem(memberNode.value);
//
//         REQUIRE(value == expectedValue);
//         REQUIRE(type == expectedType);
//     }
// } // namespace yogi::visitor::nodes
