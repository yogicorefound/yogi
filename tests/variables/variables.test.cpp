//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <random>
#include "includes/cromio/cromio.h"
#include "libs/catch2/catch_amalgamated.hpp"

long long randomInt(const long long min, const long long max) {
    static std::random_device rd; // non-deterministic seed
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution dist(min, max);

    return dist(gen);
}

double randomDouble(const double min, const double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution dist(min, max);

    return dist(gen);
}

namespace cromio::visitor::nodes {
    // Random  signed integer values
    std::string int8 = std::to_string(randomInt(INT8_MIN, INT8_MAX));
    std::string int16 = std::to_string(randomInt(INT16_MIN, INT16_MAX));
    std::string int32 = std::to_string(randomInt(INT32_MIN, INT32_MAX));
    std::string int64 = std::to_string(randomInt(INT64_MIN, INT64_MAX));

    // Random  signed integer values
    std::string uint8 = std::to_string(randomInt(0, INT8_MAX));
    std::string uint16 = std::to_string(randomInt(0, INT16_MAX));
    std::string uint32 = std::to_string(randomInt(0, INT32_MAX));
    std::string uint64 = std::to_string(randomInt(0, INT64_MAX));

    // Random floating point values
    std::string float32 = std::to_string(randomDouble(0, 2000));
    std::string float64 = std::to_string(randomDouble(0, 2000));

    TEST_CASE("variables evaluation", "[VARIABLE]", ) {
        const auto cases = GENERATE(
            // Signed integer
            std::make_tuple<std::string>("int8 a = " + int8, "int", "a", int8),
            std::make_tuple<std::string>("int16 a = " + int16, "int", "a", int16),
            std::make_tuple<std::string>("int32 a = " + int32, "int", "a", int32),
            std::make_tuple<std::string>("int a = " + int32, "int", "a", int32),
            std::make_tuple<std::string>("int64 a = " + int64, "int", "a", int64),

            // Underscores in integer
            std::make_tuple<std::string>("int a = 1_000_000", "int", "a", "1_000_000"),

            // Integer in hexadecimal
            std::make_tuple<std::string>("int a = 0xFF", "int", "a", "0xFF"),
            std::make_tuple<std::string>("int a = 0xbb", "int", "a", "0xbb"),

            // Integer in octal
            std::make_tuple<std::string>("int a = 0o755", "int", "a", "0o755"),
            std::make_tuple<std::string>("int a = 0o55", "int", "a", "0o55"),

            // Integer in binary
            std::make_tuple<std::string>("int a = 0b10", "int", "a", "0b10"),
            std::make_tuple<std::string>("int a = 0b101010", "int", "a", "0b101010"),

            // // Unsigned integer
            std::make_tuple<std::string>("uint8 a = " + uint8, "int", "a", uint8),
            std::make_tuple<std::string>("uint16 a = " + uint16, "int", "a", uint16),
            std::make_tuple<std::string>("uint32 a = " + uint32, "int", "a", uint32),
            std::make_tuple<std::string>("uint64 a = " + uint64, "int", "a", uint64),

            // Float
            std::make_tuple<std::string>("float a = " + float32, "float", "a", float32),
            std::make_tuple<std::string>("float32 a = " + float32, "float", "a", float32),
            std::make_tuple<std::string>("float64 a = " + float64, "float", "a", float64),

            // Exponent Notation
            std::make_tuple<std::string>("float a = 1e6", "float", "a", "1e6"),
            std::make_tuple<std::string>("float a = 1e-6", "float", "a", "1e-6"),

            // Boolean
            std::make_tuple<std::string>("bool a = true", "bool", "a", "1"),
            std::make_tuple<std::string>("bool a = false", "bool", "a", "0"),

            // String
            std::make_tuple<std::string>("str a = \"Hello, world!!!\"", "str", "a", "Hello, world!!!"),
            std::make_tuple<std::string>("str a = \"String\" + \" \" + \"Concatenation\"", "str", "a", "String Concatenation")

        );

        auto [text, type, name, expectedValue] = cases;

        const auto ast = Cromio::testAST(text);
        const auto& node = std::any_cast<VariableDeclarationNode>(ast.body[0].children.at(0));
        const auto [resolvedType, resolvedValue, resolvedNode] = utils::Helpers::resolveItem(node.value);

        std::cout << "Resolved type: " << resolvedType << " ExpectedValue type: " << type << std::endl;

        REQUIRE(node.kind == Kind::VARIABLE_DECLARATION);
        REQUIRE(resolvedValue == expectedValue);
        REQUIRE(resolvedType == type);
        REQUIRE(resolvedNode.type() == node.value.type());
    }

} // namespace cromio::visitor::nodes
