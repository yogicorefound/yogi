//
// Created by Brayhan De Aza on 10/19/25.
//

#include "Helpers.h"
#include <utils/errors/Errors.h>
#include <visitors/nodes/nodes.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <openssl/sha.h>

#include "antlr4-runtime.h"
#include "libs/uni-algo/include/uni_algo/norm.h"
#include "utils/helpers/visitor/variables.h"

namespace yogi::utils {
    std::string Helpers::getBuildDirectory() {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) == nullptr) {
            perror("getcwd");
        }

        return cwd;
    }

    bool Helpers::areCanonicallyEqual(const std::string &str1, const std::string &str2) {
        const std::string norm1 = una::norm::to_nfc_utf8(str1);
        const std::string norm2 = una::norm::to_nfc_utf8(str2);

        return norm1 == norm2;
    }

    bool Helpers::checkDataType(const std::string &dataType, const std::string &returnType) {
        if (dataType == "int" || dataType == "int8" || dataType == "int16" || dataType == "int32" || dataType == "int64") {
            return returnType == "int";
        }

        if (dataType == "uint" || dataType == "uint8" || dataType == "uint16" || dataType == "uint32" || dataType == "uint64") {
            return returnType == "int";
        }

        if (dataType == "float" || dataType == "float32" || dataType == "float64") {
            return returnType == "float";
        }

        if (dataType == "bool") {
            return returnType == "bool";
        }

        if (dataType == "str") {
            return returnType == "str";
        }

        if (dataType == "regex") {
            return returnType == "regex";
        }

        return false;
    }

    std::string Helpers::formatFloatNumberDecimal(const std::string &text, const int maxDecimals = -1) {
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

    long long Helpers::parseNumberString(const std::string &raw) {
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

    std::string Helpers::parseString(const std::string &rawInput) {
        std::string raw = rawInput;

        // Helper lambdas for starts_with and ends_with (C++11 compatible)
        auto starts_with = [](const std::string &str, const std::string &prefix) { return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0; };
        auto ends_with = [](const std::string &str, const std::string &suffix) { return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0; };

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

    json Helpers::getPosition(const antlr4::Token *token) {
        json pos;
        pos["line"] = token->getLine();
        pos["column"] = token->getCharPositionInLine();
        return pos;
    }

    json Helpers::createNode(const std::string &raw, const std::string &kind, const antlr4::Token *start, const antlr4::Token *stop) {
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

    json Helpers::nodeToJson(const std::any &node) {
        using namespace yogi::visitor::nodes;

        if (!node.has_value())
            return nullptr;

        // Entry
        if (node.type() == typeid(ASTNode)) {
            const auto &n = std::any_cast<const ASTNode &>(node);
            return {{"kind", "Entry"}, {"path", n.path}, {"program", nodeToJson(n.program)}};
        }

        // ExportDeclarationNode
        if (node.type() == typeid(ExportNode)) {
            const auto &n = std::any_cast<const ExportNode &>(node);
            return {
                {"kind", n.kind == Kind::ExportDefault ? "ExportDefaultStatement" : "ExportStatement"},
                {"alias", n.alias.has_value() ? nodeToJson(*n.alias) : nullptr},
                {"declaration", nodeToJson(n.declaration)}
            };
        }

        // ExportListNode
        if (node.type() == typeid(ExportListNode)) {
            const auto &n = std::any_cast<const ExportListNode &>(node);

            json modules = json::array();
            for (const auto e: n.exports) {
                modules.push_back(nodeToJson(e));
            }

            return {
                {"kind", n.kind == Kind::ExportDefault ? "ExportDefaultStatement" : "ExportListStatement"},
                {"declarations", modules}
            };
        }


        // -------------------------------------------------
        // Literals
        // -------------------------------------------------
        if (node.type() == typeid(IntegerLiteralNode)) {
            const auto &n = std::any_cast<const IntegerLiteralNode &>(node);
            return {{"kind", "IntegerLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(ImportWithoutBracketsNode)) {
            const auto &n = std::any_cast<const ImportWithoutBracketsNode &>(node);
            return {{"kind", "ImportWithoutBrackets"}, {"path", n.path}, {"name", n.name}};
        }

        if (node.type() == typeid(ImportWithBracketsNode)) {
            const auto &nodes = std::any_cast<const ImportWithBracketsNode &>(node);

            json modules = json::array();
            for (const auto n: nodes.modules) {
                modules.push_back(nodeToJson(n));
            }

            return {{"kind", "ImportWithBrackets"}, {"modules", modules}, {"path", nodes.path}};
        }


        if (node.type() == typeid(FloatLiteralNode)) {
            const auto &n = std::any_cast<const FloatLiteralNode &>(node);
            return {{"kind", "FloatLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(StringLiteralNode)) {
            const auto &n = std::any_cast<const StringLiteralNode &>(node);
            return {{"kind", "StringLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(std::vector<StringLiteralNode>)) {
            const auto &strLiteral = std::any_cast<const std::vector<StringLiteralNode> &>(node);

            json elements = json::array();
            for (const auto &s: strLiteral) {
                elements.push_back(nodeToJson(s));
            }
            return elements;
        }

        if (node.type() == typeid(RegexLiteralNode)) {
            const auto &n = std::any_cast<const RegexLiteralNode &>(node);
            return {{"kind", "RegexLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(BooleanLiteralNode)) {
            const auto &n = std::any_cast<const BooleanLiteralNode &>(node);
            return {{"kind", "BooleanLiteral"}, {"value", n.value == "1"}};
        }

        if (node.type() == typeid(NoneLiteralNode)) {
            const auto &n = std::any_cast<const NoneLiteralNode &>(node);
            return {{"kind", "NoneLiteral"}, {"value", n.value}};
        }

        if (node.type() == typeid(IdentifierLiteral)) {
            const auto &n = std::any_cast<const IdentifierLiteral &>(node);
            return {{"kind", "IdentifierLiteral"}, {"value", n.value}};
        }

        // -------------------------------------------------
        // Array element (IMPORTANT FIX)
        // -------------------------------------------------

        if (node.type() == typeid(std::vector<ArrayElementNode>)) {
            const auto &n = std::any_cast<const std::vector<ArrayElementNode> &>(node);

            json elements = json::array();
            for (const auto &el: n) {
                auto rNode = resolveItem(node);
                elements.push_back(nodeToJson(el));
            }

            return {{"kind", "ArrayElements"}, {"elements", elements}};
        }

        if (node.type() == typeid(MemberExpressionNode)) {
            const auto &n = std::any_cast<MemberExpressionNode>(node);
            // const auto items = std::any_cast<std::vector<std::any>>(n.value);

            return {{"kind", "Members"}, {"values", nodeToJson(n.value)}};
        }

        if (node.type() == typeid(ArrayElementNode)) {
            const auto &n = std::any_cast<const ArrayElementNode &>(node);
            return nodeToJson(n.value); // unwrap
        }

        // -------------------------------------------------
        // Expressions
        // -------------------------------------------------

        if (node.type() == typeid(BinaryExpressionNode)) {
            const auto &n = std::any_cast<const BinaryExpressionNode &>(node);
            auto expr = evaluateExpression(node);

            return {{"kind", "BinaryExpression"}, {"operator", n.op}, {"resultType", expr.type}, {"value", expr.value}, {"left", nodeToJson(n.left)}, {"right", nodeToJson(n.right)}};
        }

        // -------------------------------------------------
        // Statements
        // -------------------------------------------------

        if (node.type() == typeid(StatementNode)) {
            const auto &n = std::any_cast<const StatementNode &>(node);

            json children = json::array();
            for (const auto &child: n.children)
                children.push_back(nodeToJson(child));

            return {{"kind", "Statement"}, {"children", children}};
        }

        if (node.type() == typeid(ProgramNode)) {
            const auto &n = std::any_cast<const ProgramNode &>(node);

            json body = json::array();
            for (const auto &stmt: n.body)
                body.push_back(nodeToJson(stmt));

            return {{"kind", "Program"}, {"body", body}};
        }

        // -------------------------------------------------
        // Declarations
        // -------------------------------------------------
        if (node.type() == typeid(VariableDeclarationNode)) {
            const auto &n = std::any_cast<const VariableDeclarationNode &>(node);
            return {{"kind", "VariableDeclaration"}, {"identifier", n.identifier}, {"type", n.varType}, {"isConstant", n.isConstant}, {"value", nodeToJson(n.value)}};
        }

        if (node.type() == typeid(ArrayDeclarationNode)) {
            const auto &n = std::any_cast<const ArrayDeclarationNode &>(node);

            json elements = json::array();
            for (const auto &el: n.elements) {
                elements.push_back(nodeToJson(el));
            }

            json dims = json::array();
            for (const auto &d: n.dimensions)
                dims.push_back(d);

            return {
                {"kind", "ArrayDeclaration"},
                {"identifier", n.identifier},
                {"elementType", n.type},
                {"dimensions", dims}, // reemplazamos "size" por "dimensions"
                {"elements", elements}
            };
        }

        if (node.type() == typeid(DictionaryDeclarationNode)) {
            const auto &n = std::any_cast<const DictionaryDeclarationNode &>(node);
            return {{"kind", "DictionaryDeclaration"}, {"identifier", n.identifier}, {"keyType", n.keyType}, {"valueType", n.valueType}, {"size", n.size}};
        }

        if (node.type() == typeid(BaseNode)) {
            const auto &n = std::any_cast<const BaseNode &>(node);
            json start = {
                {"line", n.start.line},
                {"column", n.start.column}
            };

            json end = {
                {"line", n.end.line},
                {"column", n.end.column}
            };

            return {
                {"start", start},
                {"end", end}
            };
        }

        // -------------------------------------------------
        // Formatted String
        // -------------------------------------------------
        if (node.type() == typeid(FormattedStringNode)) {
            const auto &n = std::any_cast<const FormattedStringNode &>(node);

            json parts = json::array();
            for (const auto &v: n.value) {
                parts.push_back(nodeToJson(v));
            }

            return {
                {"kind", "FormattedString"},
                {"value", parts}
            };
        }

        // -------------------------------------------------
        // Fallback
        // -------------------------------------------------
        if (node.type() == typeid(IfStatementNode)) {
            const auto &n = std::any_cast<const IfStatementNode &>(node);

            json branchesJson = json::array();
            for (const auto &[bCondition, bBody]: n.branches) {
                json branchJson;

                // condition is null for "else"
                if (bCondition.has_value()) {
                    branchJson["condition"] = nodeToJson(bCondition); // ✅ Added .value()
                    branchJson["kind"] = "IF_STATEMENT";
                } else {
                    branchJson["condition"] = nullptr;
                    branchJson["kind"] = "ELSE_STATEMENT";
                }

                // body
                json body = json::array();
                for (const auto &stmt: bBody) {
                    body.push_back(nodeToJson(stmt));
                }
                branchJson["body"] = body;
                branchesJson.push_back(branchJson);
            }

            return {{"kind", "IF_STATEMENT"}, {"branches", branchesJson}};
        }

        return {{"kind", "Unknown"}, {"type", node.type().name()}};
    }

    // Print AST nodes in JSON-like format
    void Helpers::printNode(const std::any &node, const int indent) {
        const json ast = nodeToJson(node);
        std::cout << ast.dump(indent) << std::endl;
    }

    Helpers::ResolvedItem Helpers::resolveItem(const std::any &itemResult) {
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
            auto expr = evaluateExpression(&n);

            return {VisitorHelpers::convertTypeToString(expr.type), expr.value, itemResult};
        }

        return {}; // unreachable
    }

    visitor::nodes::Kind Helpers::resolveKind(const std::any &itemResult) {
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

    std::string Helpers::resolveDataType(const std::any &itemResult) {
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
            auto expr = evaluateExpression(n);
            return expr.value;
        }

        auto n = std::any_cast<visitor::nodes::NoneLiteralNode>(itemResult);
        return n.value;
    }


    std::filesystem::path Helpers::pathNormalizer(const std::filesystem::path &path) {
        try {
            return std::filesystem::weakly_canonical(path);
        } catch (...) {
            // fallback if path doesn't exist yet
            return std::filesystem::absolute(path);
        }
    }

    // -------------------------
    // Resolve import path
    // -------------------------

    std::filesystem::path Helpers::pathResolver(const std::filesystem::path &currentFile, const std::string &importPath) {
        const std::filesystem::path currentDir = currentFile;
        const std::filesystem::path combined = currentDir / importPath;

        return pathNormalizer(combined);
    }

    // -------------------------
    // Module ID (hash of absolute path)
    // -------------------------

    std::string Helpers::pathModuleId(const std::filesystem::path &absolutePath) {
        return hashString(absolutePath.string());
    }

    // -------------------------
    // Hash helpers
    // -------------------------
    std::string Helpers::hashString(const std::string &input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(hash[i]);
        }

        return ss.str();
    }

    std::string Helpers::removeQuotes(std::string str) {
        str.erase(
            std::ranges::remove(str, '"').begin(),
            str.end()
        );
        return str;
    };


} // namespace yogi::utils