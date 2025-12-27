//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "antlr4-runtime.h"
#include "libs/json.hpp"
#include "math/math.h"

using json = nlohmann::ordered_json;

namespace yogi::utils {
    class Helpers : public helpers::Math {
        static json getPosition(const antlr4::Token* token);

       public:
        static long long parseInteger(std::string raw);
        static double parseFloat(std::string raw);
        static long long parseNumberString(const std::string& raw);
        static std::string formatFloatNumberDecimal(const std::string& text, int maxDecimals);

        static std::string toUpper(std::string s);
        static std::string toLower(std::string s);
        static std::string toTitle(std::string s);
        static std::string trim(std::string s);
        static std::string trimStart(std::string s);
        static std::string trimEnd(std::string s);

        static json createNode(const std::string& raw, const std::string& kind, const antlr4::Token* start, const antlr4::Token* stop);
        static std::string parseString(const std::string& rawInput);

        static void printNode(const std::any& node, int indent = 0);
        static void printIndent(int indent);
        static json nodeToJson(const std::any& node);

        static ResolvedItem resolveItem(const std::any& itemResult);
    };
} // namespace yogi::utils
