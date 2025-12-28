//
// Created by Brayhan De Aza on 10/19/25.
//

#include "Helpers.h"
#include <ast/nodes/nodes.h>
#include <utils/errors/Errors.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include "antlr4-runtime.h"

namespace yogi::utils {

    std::vector<std::string> Helpers::split(const std::string& text, const std::variant<std::string, std::regex>& pattern) {
        std::vector<std::string> result;

        if (std::holds_alternative<std::string>(pattern)) {
            const std::string& sep = std::get<std::string>(pattern);

            if (sep.empty()) {
                // Optional: split into characters
                for (char c : text) {
                    result.emplace_back(1, c);
                }
                return result;
            }

            size_t start = 0;
            size_t pos;

            while ((pos = text.find(sep, start)) != std::string::npos) {
                result.push_back(text.substr(start, pos - start));
                start = pos + sep.length();
            }

            result.push_back(text.substr(start));
            return result;
        }

        const std::regex& rx = std::get<std::regex>(pattern);

        std::sregex_token_iterator it(text.begin(), text.end(), rx, -1);
        std::sregex_token_iterator end;

        for (; it != end; ++it) {
            result.push_back(it->str());
        }

        return result;
    }

    std::string Helpers::replace(const std::string& input, const std::variant<std::string, std::regex>& search, const std::string& replacement) {
        std::string result;

        if (std::holds_alternative<std::string>(search)) {
            // Reemplazo literal
            const std::string& literal = std::get<std::string>(search);
            if (literal.empty()) {
                throw std::runtime_error("replace(): search string cannot be empty");
            }

            size_t pos = 0;
            size_t found;
            while ((found = input.find(literal, pos)) != std::string::npos) {
                result.append(input, pos, found - pos);
                result.append(replacement);
                pos = found + literal.size();
            }
            result.append(input, pos, input.size() - pos);
        } else if (std::holds_alternative<std::regex>(search)) {
            // Reemplazo usando regex
            const std::regex& re = std::get<std::regex>(search);
            result = std::regex_replace(input, re, replacement);
        }

        return result;
    }

    std::string Helpers::formatFloatNumberDecimal(const std::string& text, const int maxDecimals = -1) {
        double value;
        try {
            value = std::stod(text);
        } catch (...) {
            return text; // si no es número válido
        }

        std::ostringstream oss;

        if (maxDecimals >= 0) {
            oss << std::fixed << std::setprecision(maxDecimals) << value;
        } else {
            oss << value;
        }

        std::string result = oss.str();

        // Eliminar ceros finales
        if (result.find('.') != std::string::npos) {
            result.erase(result.find_last_not_of('0') + 1);

            // Eliminar el punto si quedó solo
            if (result.back() == '.') {
                result.pop_back();
            }
        }

        return result;
    }

    std::string Helpers::toUpper(std::string s) {
        std::ranges::transform(s, s.begin(), [](const unsigned char c) { return std::toupper(c); });
        return s;
    }

    std::string Helpers::trimStart(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        return s;
    }

    std::string Helpers::trimEnd(std::string s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
        return s;
    }

    std::string Helpers::trim(std::string s) {
        auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };

        // left trim
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));

        // right trim
        s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());

        return s;
    }

    std::string Helpers::toLower(std::string s) {
        std::ranges::transform(s, s.begin(), [](const unsigned char c) { return std::tolower(c); });
        return s;
    }

    std::string Helpers::toTitle(std::string s) {
        bool newWord = true;
        for (char& c : s) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                newWord = true;
            } else if (newWord) {
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                newWord = false;
            } else {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }
        return s;
    }

    long long Helpers::parseNumberString(const std::string& raw) {
        try {
            // Binary: 0bXXXX
            if (raw.rfind("0b", 0) == 0 || raw.rfind("0B", 0) == 0)
                return std::stoll(raw.substr(2), nullptr, 2);

            // Octal: 0oXXXX
            if (raw.rfind("0o", 0) == 0 || raw.rfind("0O", 0) == 0)
                return std::stoll(raw.substr(2), nullptr, 8);

            // Hex: 0xXXXX
            if (raw.rfind("0x", 0) == 0 || raw.rfind("0X", 0) == 0)
                return std::stoll(raw.substr(2), nullptr, 16);

            // Decimal (normal or with underscore separated)
            return std::stoll(raw, nullptr, 10);
        } catch (...) {
            return 0; // fallback
        }
    }

    long long Helpers::parseInteger(std::string raw) {
        bool isNegative = false;

        // Detect negative sign
        if (!raw.empty() && raw[0] == '-') {
            isNegative = true;
            raw = raw.substr(1); // remove the '-'
        }

        if (!raw.empty() && raw[0] == '+') {
            isNegative = false;
            raw = raw.substr(1); // remove the '+'
        }

        int base = 10;

        // Detect prefix
        if (raw.rfind("0x", 0) == 0 || raw.rfind("0X", 0) == 0) {
            base = 16;
            raw = raw.substr(2);
        } else if (raw.rfind("0b", 0) == 0 || raw.rfind("0B", 0) == 0) {
            base = 2;
            raw = raw.substr(2);
        } else if (raw.rfind("0o", 0) == 0 || raw.rfind("0O", 0) == 0) {
            base = 8;
            raw = raw.substr(2);
        } else if (raw.size() > 1 && raw[0] == '0' && std::isdigit(raw[1])) {
            base = 8; // old-style octal like 0755
        }

        std::erase(raw, '_');

        long long value = std::stoll(raw, nullptr, base);
        if (isNegative)
            value = -value;

        return value;
    }

    std::string Helpers::parseString(const std::string& rawInput) {
        std::string raw = rawInput;

        // Helper lambdas for starts_with and ends_with (C++11 compatible)
        auto starts_with = [](const std::string& str, const std::string& prefix) { return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0; };
        auto ends_with = [](const std::string& str, const std::string& suffix) { return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0; };

        // 1️⃣ Detect triple-quoted string ("""...""" or '''...''')
        bool triple = false;
        if (raw.size() >= 6) {
            if ((starts_with(raw, R"(""")") && ends_with(raw, R"(""")")) || (starts_with(raw, "'''") && ends_with(raw, "'''"))) {
                triple = true;
                raw = raw.substr(3, raw.size() - 6);
            }
        }

        // 2️⃣ If not triple, strip single outer quotes
        if (!triple && raw.size() >= 2 && ((raw.front() == '"' && raw.back() == '"') || (raw.front() == '\'' && raw.back() == '\''))) {
            raw = raw.substr(1, raw.size() - 2);
        }

        // 3️⃣ Process escape sequences (skip for triple-quoted raw style)
        std::string result;
        result.reserve(raw.size());

        for (size_t i = 0; i < raw.size(); ++i) {
            if (!triple && raw[i] == '\\' && i + 1 < raw.size()) {
                switch (char next = raw[++i]) {
                    case 'n':
                        result += '\n';
                        break;
                    case 'r':
                        result += '\r';
                        break;
                    case 't':
                        result += '\t';
                        break;
                    case '\\':
                        result += '\\';
                        break;
                    case '"':
                        result += '"';
                        break;
                    case '\'':
                        result += '\'';
                        break;
                    case 'b':
                        result += '\b';
                        break;
                    case 'f':
                        result += '\f';
                        break;
                    case 'u':
                        result += '?'; // placeholder for \uXXXX
                        i += 4;
                        break;
                    default:
                        result += next;
                        break;
                }
            } else {
                result += raw[i];
            }
        }

        // 4️⃣ Normalize line endings for triple-quoted strings (optional)
        if (triple) {
            std::string normalized;
            normalized.reserve(result.size());
            for (size_t i = 0; i < result.size(); ++i) {
                if (result[i] == '\r' && i + 1 < result.size() && result[i + 1] == '\n')
                    continue;
                normalized += result[i];
            }
            return normalized;
        }

        return result;
    }

    json Helpers::getPosition(const antlr4::Token* token) {
        json pos;
        pos["line"] = token->getLine();
        pos["column"] = token->getCharPositionInLine();
        return pos;
    }

    json Helpers::createNode(const std::string& raw, const std::string& kind, const antlr4::Token* start, const antlr4::Token* stop) {
        json node;
        node["kind"] = kind;
        node["start"] = getPosition(start);
        node["end"] = getPosition(stop ? stop : start);

        if (raw.empty() != true)
            node["raw"] = raw;

        return node;
    }

    double Helpers::parseFloat(std::string raw) {
        bool isNegative = false;

        if (!raw.empty() && raw[0] == '-') {
            isNegative = true;
            raw = raw.substr(1);
        }

        // Remove all underscores
        std::erase(raw, '_');

        double value = std::stod(raw);

        if (isNegative)
            value = -value;

        return value;
    }
    // Helper function to get kind name as string
    std::string getKindName(const visitor::nodes::Kind kind) {
        using Kind = visitor::nodes::Kind;
        switch (kind) {
            case Kind::INTEGER_LITERAL:
                return "IntegerLiteral";
            case Kind::FLOAT_LITERAL:
                return "FloatLiteral";
            case Kind::STRING_LITERAL:
                return "StringLiteral";
            case Kind::BOOLEAN_LITERAL:
                return "BooleanLiteral";
            case Kind::NONE_LITERAL:
                return "NoneLiteral";
            case Kind::IDENTIFIER_LITERAL:
                return "IdentifierLiteral";
            case Kind::FORMATTED_STRING:
                return "FormattedString";
            case Kind::BINARY_EXPRESSION:
                return "BinaryExpression";
            case Kind::CONCATENATION_EXPRESSION:
                return "ConcatenationExpression";
            case Kind::STATEMENT:
                return "Statement";
            case Kind::VARIABLE_DECLARATION:
                return "VariableDeclaration";
            case Kind::ARRAY_DECLARATION:
                return "ArrayDeclaration";
            case Kind::ARRAY_ELEMENT:
                return "ArrayElement";
            case Kind::DICTIONARY_DECLARATION:
                return "DictionaryDeclaration";
            case Kind::DICTIONARY_PAIR:
                return "DictionaryPair";
            case Kind::PROGRAM:
                return "Program";
            default:
                return "Unknown";
        }
    }

    // Print indentation
    void Helpers::printIndent(const int indent) {
        for (int i = 0; i < indent; i++) {
            std::cout << "  ";
        }
    }

    json Helpers::nodeToJson(const std::any& node) {
        using namespace yogi::visitor::nodes;

        if (!node.has_value())
            return nullptr;

        // -------------------------------------------------
        // Literals
        // -------------------------------------------------

        if (node.type() == typeid(IntegerLiteralNode)) {
            const auto& n = std::any_cast<const IntegerLiteralNode&>(node);
            return {{"kind", "IntegerLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(FloatLiteralNode)) {
            const auto& n = std::any_cast<const FloatLiteralNode&>(node);
            return {{"kind", "FloatLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(StringLiteralNode)) {
            const auto& n = std::any_cast<const StringLiteralNode&>(node);
            return {{"kind", "StringLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(std::vector<StringLiteralNode>)) {
            const auto& strLiteral = std::any_cast<const std::vector<StringLiteralNode>&>(node);

            json elements = json::array();;
            for (auto s : strLiteral) {
                elements.push_back(nodeToJson(s));
            }
            return elements;
        }

        if (node.type() == typeid(RegexLiteralNode)) {
            const auto& n = std::any_cast<const RegexLiteralNode&>(node);
            return {{"kind", "RegexLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(BooleanLiteralNode)) {
            const auto& n = std::any_cast<const BooleanLiteralNode&>(node);
            return {{"kind", "BooleanLiteral"}, {"value", n.value == "1"}};
        }

        if (node.type() == typeid(NoneLiteralNode)) {
            const auto& n = std::any_cast<const NoneLiteralNode&>(node);
            return {{"kind", "NoneLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(IdentifierLiteral)) {
            const auto& n = std::any_cast<const IdentifierLiteral&>(node);
            return {{"kind", "IdentifierLiteral"}, {"value", n.value}};
        }

        // -------------------------------------------------
        // Array element (IMPORTANT FIX)
        // -------------------------------------------------

        if (node.type() == typeid(std::vector<ArrayElementNode>)) {
            const auto& n = std::any_cast<const std::vector<ArrayElementNode>&>(node);

            json elements = json::array();
            for (const auto& el : n) {
                elements.push_back(nodeToJson(el));
            }

            return {{"kind", "ArrayElements"}, {"elements", elements}};
        }

        if (node.type() == typeid(MemberExpressionNode)) {
            const auto& n = std::any_cast<MemberExpressionNode>(node);
            std::cout << "MemberExpressionNode: " << n.value.type().name();
            const auto items = std::any_cast<std::vector<std::any>>(n.value);

            return {{"kind", "Members"}, {"values", nodeToJson(n.value)}};
        }

        if (node.type() == typeid(ArrayElementNode)) {
            const auto& n = std::any_cast<const ArrayElementNode&>(node);
            return nodeToJson(n.value); // unwrap
        }

        // -------------------------------------------------
        // Expressions
        // -------------------------------------------------

        if (node.type() == typeid(BinaryExpressionNode)) {
            const auto& n = std::any_cast<const BinaryExpressionNode&>(node);
            return {{"kind", "BinaryExpression"}, {"operator", n.op}, {"resultType", n.resultType}, {"value", n.value}, {"left", nodeToJson(n.left)}, {"right", nodeToJson(n.right)}};
        }

        // -------------------------------------------------
        // Statements
        // -------------------------------------------------

        if (node.type() == typeid(StatementNode)) {
            const auto& n = std::any_cast<const StatementNode&>(node);

            json children = json::array();
            for (const auto& child : n.children)
                children.push_back(nodeToJson(child));

            return {{"kind", "Statement"}, {"children", children}};
        }

        if (node.type() == typeid(ProgramNode)) {
            const auto& n = std::any_cast<const ProgramNode&>(node);

            json body = json::array();
            for (const auto& stmt : n.body)
                body.push_back(nodeToJson(stmt));

            return {{"kind", "Program"}, {"body", body}};
        }

        // -------------------------------------------------
        // Declarations
        // -------------------------------------------------
        if (node.type() == typeid(VariableDeclarationNode)) {
            const auto& n = std::any_cast<const VariableDeclarationNode&>(node);
            return {{"kind", "VariableDeclaration"}, {"identifier", n.identifier}, {"type", n.varType}, {"isConstant", n.isConstant}, {"value", nodeToJson(n.value)}};
        }

        if (node.type() == typeid(ArrayDeclarationNode)) {
            const auto& n = std::any_cast<const ArrayDeclarationNode&>(node);

            json elements = json::array();
            for (const auto& el : n.elements)
                elements.push_back(nodeToJson(el));

            return {{"kind", "ArrayDeclaration"}, {"identifier", n.identifier}, {"elementType", n.type}, {"size", n.size}, {"elements", elements}};
        }

        if (node.type() == typeid(DictionaryDeclarationNode)) {
            const auto& n = std::any_cast<const DictionaryDeclarationNode&>(node);
            return {{"kind", "DictionaryDeclaration"}, {"identifier", n.identifier}, {"keyType", n.keyType}, {"valueType", n.valueType}, {"size", n.size}};
        }

        // -------------------------------------------------
        // Formatted String
        // -------------------------------------------------

        if (node.type() == typeid(FormattedStringNode)) {
            const auto& n = std::any_cast<const FormattedStringNode&>(node);

            json params = json::array();
            for (const auto& p : n.params)
                params.push_back(nodeToJson(p));

            return {{"kind", "FormattedString"}, {"value", n.value}, {"params", params}};
        }

        // -------------------------------------------------
        // Fallback
        // -------------------------------------------------

        return {{"kind", "Unknown"}, {"type", node.type().name()}};
    }
    // Print AST nodes in JSON-like format
    void Helpers::printNode(const std::any& node, const int indent) {
        const json ast = nodeToJson(node);
        std::cout << ast.dump(indent) << std::endl;
    }

    Helpers::ResolvedItem Helpers::resolveItem(const std::any& itemResult) {
        if (itemResult.type() == typeid(visitor::nodes::IntegerLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::IntegerLiteralNode>(itemResult);
            return {"int", n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::FloatLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::FloatLiteralNode>(itemResult);
            return {"float", n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::StringLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::StringLiteralNode>(itemResult);
            return {"str", n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::RegexLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::RegexLiteralNode>(itemResult);
            return {"regex", n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::BooleanLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::BooleanLiteralNode>(itemResult);
            return {"bool", n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::BinaryExpressionNode)) {
            auto n = std::any_cast<visitor::nodes::BinaryExpressionNode>(itemResult);
            return {n.resultType, n.value, itemResult};
        }

        return {}; // unreachable
    }

    visitor::nodes::Kind Helpers::resolveKind(const std::any& itemResult) {
        if (itemResult.type() == typeid(visitor::nodes::IntegerLiteralNode)) {
            return visitor::nodes::Kind::INTEGER_LITERAL;
        }

        if (itemResult.type() == typeid(visitor::nodes::FloatLiteralNode)) {
            return visitor::nodes::Kind::FLOAT_LITERAL;
        }

        if (itemResult.type() == typeid(visitor::nodes::StringLiteralNode)) {
            return visitor::nodes::Kind::STRING_LITERAL;
        }

        if (itemResult.type() == typeid(visitor::nodes::RegexLiteralNode)) {
            return visitor::nodes::Kind::REGEX_LITERAL;
        }

        if (itemResult.type() == typeid(visitor::nodes::BooleanLiteralNode)) {
            return visitor::nodes::Kind::BOOLEAN_LITERAL;
        }

        if (itemResult.type() == typeid(visitor::nodes::BinaryExpressionNode)) {
            return visitor::nodes::Kind::BINARY_EXPRESSION;
        }

        return visitor::nodes::Kind::NONE_LITERAL;
    }

    std::string Helpers::resolveDataType(const std::any& itemResult) {
        if (itemResult.type() == typeid(visitor::nodes::IntegerLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::IntegerLiteralNode>(itemResult);
            return n.value;
        }

        if (itemResult.type() == typeid(visitor::nodes::FloatLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::FloatLiteralNode>(itemResult);
            return n.value;
        }

        if (itemResult.type() == typeid(visitor::nodes::StringLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::StringLiteralNode>(itemResult);
            return n.value;
        }

        if (itemResult.type() == typeid(visitor::nodes::RegexLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::RegexLiteralNode>(itemResult);
            return n.value;
        }

        if (itemResult.type() == typeid(visitor::nodes::BooleanLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::BooleanLiteralNode>(itemResult);
            return n.value;
        }

        if (itemResult.type() == typeid(visitor::nodes::BinaryExpressionNode)) {
            auto n = std::any_cast<visitor::nodes::BinaryExpressionNode>(itemResult);
            return n.value;
        }

        auto n = std::any_cast<visitor::nodes::NoneLiteralNode>(itemResult);
        return n.value;
    }

} // namespace yogi::utils