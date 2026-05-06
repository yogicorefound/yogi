//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include <visitors/nodes/BaseNode.h>
#include <regex>
#include "antlr4-runtime.h"
#include "libs/json.hpp"
#include "math/math.h"
#include "members/members.h"
#include "nodes/nodes.h"

using json = nlohmann::ordered_json;

namespace yogi::utils {
    class Helpers : public helpers::Math, public helpers::Members, public helpers::Nodes {
        static json getPosition(const antlr4::Token *token);

        public:
            static long long parseInteger(std::string raw);

            static double parseFloat(std::string raw);

            static long long parseNumberString(const std::string &raw);

            static std::string formatFloatNumberDecimal(const std::string &text, int maxDecimals);

            static bool checkDataType(const std::string &dataType, const std::string &returnType);

            static json createNode(const std::string &raw, const std::string &kind, const antlr4::Token *start, const antlr4::Token *stop);

            static std::string parseString(const std::string &rawInput);

            static void printNode(const std::any &node, int indent = 0);

            static void printIndent(int indent);

            static json nodeToJson(const std::any &node);

            static ResolvedItem resolveItem(const std::any &itemResult);

            static visitor::nodes::Kind resolveKind(const std::any &itemResult);

            static std::string resolveDataType(const std::any &itemResult);

            static bool areCanonicallyEqual(const std::string &str1, const std::string &str2);
    };
} // namespace yogi::utils