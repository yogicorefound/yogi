//
// Created by Brayhan De Aza on 12/2/25.
//

#include "Arrays.h"
#include <charconv>
#include "semantic/variables/Variables.h"

namespace cromio::semantic {
    json Arrays::analyzeArrayDeclaration(const json& node, const std::string& source) {
        const std::string type = node["Type"]["raw"];
        const std::string size = node["Type"]["size"];
        const std::string identifier = node["Identifier"]["value"];

        const auto items = node["value"]["items"];
        if (const int length = items.size(); size != "auto" && length > std::stoi(size)) {
            utils::Errors::throwRangeError("Expected array size of " + size + ", but received " + std::to_string(length) + " elements.", node["value"], source);
        }

        return node;
    }

    void Arrays::analyzeArrayItems(const std::string& identifier, const std::string& returnType, const std::string& rValue, const std::string& boolValue, const std::string& dataType, const std::any& node, const std::string& source) {
        analyze64BitInteger(rValue, dataType, identifier, source, node);

        if (dataType.find("uint") != std::string::npos) {
            analyzeUnsignedInteger(rValue, dataType, identifier, source, node);
        } else if (dataType.find("int") != std::string::npos) {
            analyzeSignedInteger(rValue, dataType, identifier, source, node);
        } else if (dataType.find("float") != std::string::npos) {
            analyzeFloat(rValue, dataType, source, node);
        } else if (dataType == "str" && returnType != "str") {
            utils::Errors::throwTypeError(identifier, dataType, node, source);
        } else if (dataType == "bool") {
            if (boolValue != "true" && boolValue != "false") {
                utils::Errors::throwTypeError(identifier, dataType, node, source);
            }
        }
    }

    Arrays::ResolvedItem Arrays::resolveItem(const std::any& itemResult, Scope* scope, const std::string& source) {
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

        if (itemResult.type() == typeid(visitor::nodes::BooleanLiteralNode)) {
            auto n = std::any_cast<visitor::nodes::BooleanLiteralNode>(itemResult);
            return {"bool", n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::BinaryExpressionNode)) {
            auto n = std::any_cast<visitor::nodes::BinaryExpressionNode>(itemResult);
            return {n.resultType, n.value, itemResult};
        }

        if (itemResult.type() == typeid(visitor::nodes::IdentifierLiteral)) {
            auto id = std::any_cast<visitor::nodes::IdentifierLiteral>(itemResult);

            auto varInfo = scope->lookup(id.value);
            if (!varInfo.has_value()) {
                utils::Errors::throwScopeError("Variable '" + id.value + "' is not declared", id.value, id, source);
            }

            // 🔥 RECURSION happens here
            return resolveItem(varInfo.value()->value, scope, source);
        }

        utils::Errors::throwError("Error", "Unsupported array element type", itemResult, source);

        return {}; // unreachable
    }

    void Arrays::processArrayItems(const std::string& arrayType, std::string& itemType, std::any& itemValue, std::string& boolValue, std::string& rValue, const std::any& itemResult, Scope* scope, const std::string& source) {
        const auto [type, value, node] = resolveItem(itemResult, scope, source);

        itemType = type;
        rValue = value;
        itemValue = node;

        if (itemType == "bool")
            boolValue = value;

        // 🔒 Single, correct validation point
        if (!checkArrayDataType(arrayType, itemType, rValue)) {
            utils::Errors::throwTypeError("Invalid array element type", arrayType, itemResult, source);
        }
    }

    bool Arrays::checkArrayDataType(const std::string& dataType, const std::string& returnType, const std::string& value) {
        // -------------------------------
        // Helpers (local lambdas allowed)
        // -------------------------------
        auto isIntType = [&](const std::string& t) { return t == "int" || t == "int8" || t == "int16" || t == "int32" || t == "int64"; };

        auto isUIntType = [&](const std::string& t) { return t == "uint" || t == "uint8" || t == "uint16" || t == "uint32" || t == "uint64"; };

        auto isFloatType = [&](const std::string& t) { return t == "float" || t == "float32" || t == "float64"; };

        auto bitWidth = [&](const std::string& t) {
            if (t == "int8" || t == "uint8")
                return 8;
            if (t == "int16" || t == "uint16")
                return 16;
            if (t == "int64" || t == "uint64")
                return 64;
            return 32; // int, uint, float → 32-bit default
        };

        // -------------------------------
        // STRING
        // -------------------------------
        if (dataType == "str")
            return returnType == "str";

        // -------------------------------
        // BOOL
        // -------------------------------
        if (dataType == "bool") {
            if (returnType != "bool")
                return false;
            return value == "true" || value == "false" || value == "0" || value == "1";
        }

        // -------------------------------
        // INTEGER (signed)
        // -------------------------------
        if (isIntType(dataType)) {
            long long v{};
            auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), v);
            if (ec != std::errc() || ptr != value.data() + value.size())
                return false;

            int bits = bitWidth(dataType);
            long long min = -(1LL << (bits - 1));
            long long max = (1LL << (bits - 1)) - 1;

            if (v < min || v > max)
                return false;

            // conversion rules
            return isIntType(returnType) || isUIntType(returnType) || isFloatType(returnType);
        }

        // -------------------------------
        // UNSIGNED INTEGER
        // -------------------------------
        if (isUIntType(dataType)) {
            unsigned long long v{};
            auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), v);
            if (ec != std::errc() || ptr != value.data() + value.size())
                return false;

            int bits = bitWidth(dataType);
            unsigned long long max = (bits == 64) ? std::numeric_limits<unsigned long long>::max() : ((1ULL << bits) - 1);

            if (v > max)
                return false;

            return returnType == "int" || isFloatType(returnType);
        }

        // -------------------------------
        // FLOAT
        // -------------------------------
        if (isFloatType(dataType)) {
            try {
                long double v = std::stold(value);
                (void)v; // value parsed successfully
            } catch (...) {
                return false;
            }

            return isFloatType(returnType) || returnType == "int";
        }

        return false;
    }

} // namespace cromio::semantic