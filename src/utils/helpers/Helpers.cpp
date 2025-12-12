//
// Created by Brayhan De Aza on 10/19/25.
//

#include "Helpers.h"
#include <visitor/nodes/nodes.h>
#include <algorithm>
#include <string>
#include "antlr4-runtime.h"

namespace cromio::utils {
    std::string Helpers::toUpper(std::string s) {
        std::ranges::transform(s, s.begin(), [](unsigned char c) { return std::toupper(c); });
        return s;
    }

    long long Helpers::parseNumberString(const std::string& raw) {
        try {
            // Binary: 0bxxxx
            if (raw.rfind("0b", 0) == 0 || raw.rfind("0B", 0) == 0)
                return std::stoll(raw.substr(2), nullptr, 2);

            // Octal: 0oxxxx
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

    std::string Helpers::trimLeadingZeros(const std::string& s) {
        size_t i = 0;
        while (i < s.size() && s[i] == '0')
            i++;
        return s.substr(i);
    }

    bool Helpers::strGreater(const std::string& a, const std::string& b) {
        return a.compare(b) > 0;
    }

    bool Helpers::exceedsUInt64(const std::string& raw) {
        static const std::string U64_MAX = "18446744073709551615"; // 2^64 - 1
        std::string s = raw;

        // Unsigned values must not have sign
        if (!s.empty() && (s[0] == '-' || s[0] == '+')) {
            return true;
        }

        s = trimLeadingZeros(s);
        if (s.empty())
            return false; // "0" is fine

        if (s.size() > U64_MAX.size())
            return true;
        if (s.size() < U64_MAX.size())
            return false;

        return strGreater(s, U64_MAX);
    }

    bool Helpers::exceedsInt64(const std::string& raw, const bool isUnsigned) {
        // Handle optional leading + or -
        bool negative = false;
        std::string s = raw;

        if (!s.empty() && (s[0] == '-' || s[0] == '+')) {
            negative = s[0] == '-';
            s = s.substr(1);
        }

        // Remove leading zeros
        s = trimLeadingZeros(s);
        if (s.empty())
            return false;

        static const std::string MAX64 = isUnsigned ? "9223372036854775807" : "18446744073709551615";
        static const std::string MIN64 = isUnsigned ? "9223372036854775808" : "18446744073709551616";

        if (negative) {
            if (s.size() > MIN64.size())
                return true;
            if (s.size() < MIN64.size())
                return false;
            return s > MIN64;
        }

        if (s.size() > MAX64.size())
            return true;
        if (s.size() < MAX64.size())
            return false;
        return s > MAX64;
    }

    bool Helpers::isGreaterUnsigned(const std::string& num, const std::string& max) {
        // remove leading zeros
        std::string a = num;
        a.erase(0, a.find_first_not_of('0'));

        if (a.size() != max.size())
            return a.size() > max.size();

        return a > max;
    }

    bool Helpers::isGreaterSigned(const std::string& num, const std::string& maxPos, const std::string& maxNeg) {
        if (num[0] == '-') {
            // remove leading '-'
            std::string absNum = num.substr(1);
            absNum.erase(0, absNum.find_first_not_of('0'));
            if (absNum.size() != maxNeg.size())
                return absNum.size() > maxNeg.size();
            return absNum > maxNeg;
        }
        std::string n = num;
        n.erase(0, n.find_first_not_of('0'));

        if (n.size() != maxPos.size())
            return n.size() > maxPos.size();

        return n > maxPos;
    }

    bool Helpers::isValidNumber(const std::string& str) {
        if (str.empty())
            return false;

        size_t i = 0;
        bool hasDecimal = false;
        bool hasDigit = false;

        if (str[0] == '+' || str[0] == '-')
            i = 1;
        if (i == str.size())
            return false;

        for (; i < str.size(); ++i) {
            if (const char c = str[i]; std::isdigit(c)) {
                hasDigit = true;
            } else if (c == '.') {
                if (hasDecimal)
                    return false;
                hasDecimal = true;
            } else if (c == 'e' || c == 'E') {
                if (i + 1 >= str.size())
                    return false;
                if (str[i + 1] == '+' || str[i + 1] == '-')
                    ++i;
            } else {
                return false;
            }
        }

        return hasDigit;
    }

    double Helpers::parseFloat(std::string raw) {
        bool isNegative = false;

        // Detect negative sign
        if (!raw.empty() && raw[0] == '-') {
            isNegative = true;
            raw = raw.substr(1);
        }

        std::erase(raw, '_');

        double value = 0.0;
        value = std::stod(raw);

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

    // Print AST nodes in JSON-like format
    void Helpers::printNode(const std::any& node, int indent) {
        using namespace cromio::visitor::nodes;

        if (!node.has_value()) {
            printIndent(indent);
            std::cout << "null";
            return;
        }

        try {
            // Integer Literal
            if (node.type() == typeid(IntegerLiteralNode)) {
                auto n = std::any_cast<IntegerLiteralNode>(node);
                printIndent(indent);
                std::cout << "{ \"kind\": \"IntegerLiteral\", \"value\": " << n.value << " }";
            }
            // Float Literal
            else if (node.type() == typeid(FloatLiteralNode)) {
                auto n = std::any_cast<FloatLiteralNode>(node);
                printIndent(indent);
                std::cout << "{ \"kind\": \"FloatLiteral\", \"value\": " << n.value << " }";
            }
            // String Literal
            else if (node.type() == typeid(StringLiteralNode)) {
                auto n = std::any_cast<StringLiteralNode>(node);
                printIndent(indent);
                std::cout << "{ \"kind\": \"StringLiteral\", \"value\": \"" << n.value << "\" }";
            }
            // Boolean Literal
            else if (node.type() == typeid(BooleanLiteralNode)) {
                auto n = std::any_cast<BooleanLiteralNode>(node);
                printIndent(indent);
                std::cout << "{ \"kind\": \"BooleanLiteral\", \"value\": " << (n.value == "1" ? "true" : "false") << " }";
            }
            // None Literal
            else if (node.type() == typeid(NoneLiteralNode)) {
                auto n = std::any_cast<NoneLiteralNode>(node);
                printIndent(indent);
                std::cout << "{ \"kind\": \"NoneLiteral\", \"value\": \"" << n.value << "\" }";
            }
            // Identifier Literal
            else if (node.type() == typeid(IdentifierLiteral)) {
                auto n = std::any_cast<IdentifierLiteral>(node);
                printIndent(indent);
                std::cout << "{ \"kind\": \"IdentifierLiteral\", \"value\": \"" << n.value << "\" }";
            }
            // Binary Expression
            else if (node.type() == typeid(BinaryExpressionNode)) {
                auto n = std::any_cast<BinaryExpressionNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"BinaryExpression\",\n";
                printIndent(indent + 1);
                std::cout << "\"operator\": \"" << n.op << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"resultType\": \"" << n.resultType << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"value\": \"" << n.value << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"left\": ";
                printNode(n.left, 0);
                std::cout << ",\n";
                printIndent(indent + 1);
                std::cout << "\"right\": ";
                printNode(n.right, 0);
                std::cout << "\n";
                printIndent(indent);
                std::cout << "}";
            }
            // Statement Node
            else if (node.type() == typeid(StatementNode)) {
                auto n = std::any_cast<StatementNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"Statement\",\n";
                printIndent(indent + 1);
                std::cout << "\"children\": [\n";
                for (size_t i = 0; i < n.children.size(); i++) {
                    printNode(n.children[i], indent + 2);
                    if (i < n.children.size() - 1)
                        std::cout << ",";
                    std::cout << "\n";
                }
                printIndent(indent + 1);
                std::cout << "]\n";
                printIndent(indent);
                std::cout << "}";
            }
            // Program Node
            else if (node.type() == typeid(ProgramNode)) {
                auto n = std::any_cast<ProgramNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"Program\",\n";
                printIndent(indent + 1);
                std::cout << "\"body\": [\n";
                for (size_t i = 0; i < n.statements.size(); i++) {
                    // Wrap StatementNode in std::any before printing
                    std::any stmtAny = n.statements[i];
                    printNode(stmtAny, indent + 2);
                    if (i < n.statements.size() - 1)
                        std::cout << ",";
                    std::cout << "\n";
                }
                printIndent(indent + 1);
                std::cout << "]\n";
                printIndent(indent);
                std::cout << "}";
            }
            // Variable Declaration
            else if (node.type() == typeid(VariableDeclarationNode)) {
                auto n = std::any_cast<VariableDeclarationNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"VariableDeclaration\",\n";
                printIndent(indent + 1);
                std::cout << "\"identifier\": \"" << n.identifier << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"type\": \"" << n.varType << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"isConstant\": " << (n.isConstant ? "true" : "false") << ",\n";
                printIndent(indent + 1);
                std::cout << "\"value\": ";
                printNode(n.value, 0);
                std::cout << "\n";
                printIndent(indent);
                std::cout << "}";
            }
            // Array Declaration
            else if (node.type() == typeid(ArrayDeclarationNode)) {
                auto n = std::any_cast<ArrayDeclarationNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"ArrayDeclaration\",\n";
                printIndent(indent + 1);
                std::cout << "\"identifier\": \"" << n.identifier << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"elementType\": \"" << n.elementType << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"size\": " << n.size << "\n";
                printIndent(indent);
                std::cout << "}";
            }
            // Dictionary Declaration
            else if (node.type() == typeid(DictionaryDeclarationNode)) {
                auto n = std::any_cast<DictionaryDeclarationNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"DictionaryDeclaration\",\n";
                printIndent(indent + 1);
                std::cout << "\"identifier\": \"" << n.identifier << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"keyType\": \"" << n.keyType << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"valueType\": \"" << n.valueType << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"size\": " << n.size << "\n";
                printIndent(indent);
                std::cout << "}";
            }
            // Formatted String
            else if (node.type() == typeid(FormattedStringNode)) {
                auto n = std::any_cast<FormattedStringNode>(node);
                printIndent(indent);
                std::cout << "{\n";
                printIndent(indent + 1);
                std::cout << "\"kind\": \"FormattedString\",\n";
                printIndent(indent + 1);
                std::cout << "\"value\": \"" << n.value << "\",\n";
                printIndent(indent + 1);
                std::cout << "\"params\": [\n";
                for (size_t i = 0; i < n.params.size(); i++) {
                    // Wrap BaseNode in std::any before printing
                    std::any paramAny = n.params[i];
                    printNode(paramAny, indent + 2);
                    if (i < n.params.size() - 1)
                        std::cout << ",";
                    std::cout << "\n";
                }
                printIndent(indent + 1);
                std::cout << "]\n";
                printIndent(indent);
                std::cout << "}";
            } else {
                printIndent(indent);
                std::cout << "{ \"kind\": \"Unknown\", \"type\": \"" << node.type().name() << "\" }";
            }
        } catch (const std::bad_any_cast& e) {
            printIndent(indent);
            std::cout << "{ \"error\": \"Bad cast: " << e.what() << "\" }";
        }
    }
} // namespace cromio::utils