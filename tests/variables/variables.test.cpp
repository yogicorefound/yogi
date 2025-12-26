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

    std::string toHex(const uint64_t value) {
        std::stringstream ss;
        ss << std::hex << value;
        return "0x" + ss.str();
    }

    template <typename T>
    std::string toBinary(T value) {
        return "0b" + std::bitset<sizeof(T) * 8>(value).to_string();
    }

    std::string toOctal(const uint64_t value) {
        std::stringstream ss;
        ss << std::oct << value;
        return "0o" + ss.str();
    }

    template <typename T>
    std::string toExponent(T value, int precision = 6) {
        std::stringstream ss;
        ss.setf(std::ios::scientific);
        ss.precision(precision);
        ss << value;
        return ss.str();
    }

    std::string toUnderscore(const std::string& number) {
        std::string s = number;
        bool neg = false;

        if (!s.empty() && s[0] == '-') {
            neg = true;
            s.erase(0, 1);
        }

        std::string out;
        int count = 0;

        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            out.insert(out.begin(), s[i]);
            count++;
            if (count == 3 && i != 0) {
                out.insert(out.begin(), '_');
                count = 0;
            }
        }

        if (neg)
            out.insert(out.begin(), '-');

        return out;
    }

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

    // Random underscore float value
    std::string underscoreFloat1 = toUnderscore(float32);
    std::string underscoreFloat2 = toUnderscore(float64);

    // Random boolean values
    std::string bool1 = randomInt(0, 1) == 1 ? "true" : "false";
    std::string bool2 = randomInt(0, 1) == 1 ? "true" : "false";

    // Random hex value
    std::string hex1 = toHex(randomInt(0, INT16_MAX));
    std::string hex2 = toHex(randomInt(0, INT16_MAX));

    // Random binary value
    std::string bin1 = toBinary(randomInt(0, INT8_MAX));
    std::string bin2 = toBinary(randomInt(0, INT8_MAX));

    // Random octal value
    std::string oct1 = toOctal(randomInt(0, INT16_MAX));
    std::string oct2 = toOctal(randomInt(0, INT16_MAX));

    // Random exponent value
    std::string exp1 = toExponent(randomDouble(0, 2000));
    std::string exp2 = toExponent(randomDouble(0, 2000));

    // Random underscore value
    std::string underscore1 = toUnderscore(std::to_string(randomInt(INT8_MIN, INT8_MAX)));
    std::string underscore2 = toUnderscore(std::to_string(randomInt(INT16_MIN, INT16_MAX)));

    TEST_CASE("variables evaluation", "[VARIABLE]", ) {
        const auto cases = GENERATE(
            // Signed integer
            std::make_tuple<std::string>("int8 a = " + int8, "int", "a", int8),
            std::make_tuple<std::string>("int16 a = " + int16, "int", "a", int16),
            std::make_tuple<std::string>("int32 a = " + int32, "int", "a", int32),
            std::make_tuple<std::string>("int a = " + int32, "int", "a", int32),
            std::make_tuple<std::string>("int64 a = " + int64, "int", "a", int64),

            // Underscores in integer
            std::make_tuple<std::string>("int a = " + underscore1, "int", "a", std::to_string(utils::Helpers::parseInteger(underscore1))),
            std::make_tuple<std::string>("int a = " + underscore2, "int", "a", std::to_string(utils::Helpers::parseInteger(underscore2))),

            // Integer in hexadecimal
            std::make_tuple<std::string>("int a = " + hex1, "int", "a", std::to_string(utils::Helpers::parseNumberString(hex1))),
            std::make_tuple<std::string>("int a = " + hex2, "int", "a", std::to_string(utils::Helpers::parseNumberString(hex2))),

            // Integer in octal
            std::make_tuple<std::string>("int a = " + oct1, "int", "a", std::to_string(utils::Helpers::parseNumberString(oct1))),
            std::make_tuple<std::string>("int a = " + oct2, "int", "a", std::to_string(utils::Helpers::parseNumberString(oct2))),

            // Integer in binary
            std::make_tuple<std::string>("int a = " + bin1, "int", "a", std::to_string(utils::Helpers::parseNumberString(bin1))),
            std::make_tuple<std::string>("int a = " + bin2, "int", "a", std::to_string(utils::Helpers::parseNumberString(bin2))),

            // Unsigned integer
            std::make_tuple<std::string>("uint8 a = " + uint8, "int", "a", uint8),
            std::make_tuple<std::string>("uint16 a = " + uint16, "int", "a", uint16),
            std::make_tuple<std::string>("uint32 a = " + uint32, "int", "a", uint32),
            std::make_tuple<std::string>("uint64 a = " + uint64, "int", "a", uint64),

            // Float
            std::make_tuple<std::string>("float a = " + float32, "float", "a", float32),
            std::make_tuple<std::string>("float32 a = " + float32, "float", "a", float32),
            std::make_tuple<std::string>("float64 a = " + float64, "float", "a", float64),
            std::make_tuple<std::string>("float a = " + underscoreFloat1, "float", "a", std::to_string(utils::Helpers::parseFloat(float32)))
            // std::make_tuple<std::string>("float64 a = " + underscoreFloat2, "float", "a", std::to_string(utils::Helpers::parseFloat(float64)))

            // // Exponent Notation
            // std::make_tuple<std::string>("float a = " + exp1, "float", "a", exp1),
            // std::make_tuple<std::string>("float a = " + exp2, "float", "a", exp2),
            //
            // // Boolean
            // std::make_tuple<std::string>("bool a = " + bool1, "bool", "a", bool1 == "true" ? "1" : "0"),
            // std::make_tuple<std::string>("bool a = " + bool2, "bool", "a", bool2 == "true" ? "1" : "0")

            // String
            // std::make_tuple<std::string>("str a = \"Hello, world!!!\"", "str", "a", "Hello, world!!!"),
            // std::make_tuple<std::string>("str a = \"String\" + \" \" + \"Concatenation\"", "str", "a", "String Concatenation"),
            // std::make_tuple<std::string>("str a = f\"Hello, {\"world!!!\"}\"", "str", "a", "Hello, world!!!")

        );

        auto [text, type, name, expectedValue] = cases;

        const auto ast = Yogi::testAST(text);
        const auto& node = std::any_cast<VariableDeclarationNode>(ast.body[0].children.at(0));
        const auto [resolvedType, resolvedValue, resolvedNode] = utils::Helpers::resolveItem(node.value);

        REQUIRE(node.kind == Kind::VARIABLE_DECLARATION);
        REQUIRE(resolvedValue == expectedValue);
        REQUIRE(resolvedType == type);
        REQUIRE(resolvedNode.type() == node.value.type());

    } // namespace yogi::visitor::nodes
} // namespace yogi::visitor::nodes