//
// Created by Brayhan De Aza on 10/19/25.
//

#ifndef CROMIO_HELPERS_H
#define CROMIO_HELPERS_H

#include "antlr4-runtime.h"
#include "libs/json.hpp"

using json = nlohmann::ordered_json;

namespace cromio::utils {
    class Helpers {
        static json getPosition(const antlr4::Token* token);

       public:
        static long long parseInteger(std::string raw);
        static double parseFloat(std::string raw);
        static long long parseNumberString(const std::string& raw);

        static std::string toUpper(std::string s);
        static json createNode(const std::string& raw, const std::string& kind, const antlr4::Token* start, const antlr4::Token* stop);
        static std::string parseString(const std::string& rawInput);
        static std::string trimLeadingZeros(const std::string& s);

        static bool exceedsInt64(const std::string& raw, bool isUnsigned);
        static bool exceedsUInt64(const std::string& raw);
        static bool strGreater(const std::string& a, const std::string& b);
        static bool isGreaterUnsigned(const std::string& num, const std::string& max);
        static bool isGreaterSigned(const std::string& num, const std::string& maxPos, const std::string& maxNeg);
        static bool isValidNumber(const std::string& str);

        static void printNode(const std::any& node, int indent = 0);
        static void printIndent(const int indent);
    };
} // namespace cromio::utils::helpers

#endif // CROMIO_HELPERS_H
