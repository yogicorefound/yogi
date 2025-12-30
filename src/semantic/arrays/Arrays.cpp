//
// Created by Brayhan De Aza on 12/2/25.
//

#include "Arrays.h"
#include <charconv>
#include "semantic/variables/Variables.h"

namespace yogi::semantic {
    void Arrays::analyzeUnOrSingedInteger(const std::string& dataType, const std::string& rValue, const std::string& identifier, const std::string& returnType, visitor::nodes::ArrayDeclarationNode& node, const std::string& source) {
        if (dataType.find("uint") != std::string::npos) {
            analyzeUnsignedInteger(rValue, dataType, identifier, source, node);

        } else if (dataType.find("int") != std::string::npos) {
            analyzeSignedInteger(rValue, dataType, identifier, source, node);

        } else if (dataType.find("float") != std::string::npos) {
            analyzeFloat(rValue, dataType, source, node);

        } else if (dataType == "str" && returnType != "str") {
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        } else if (dataType == "bool") {
            utils::Errors::throwTypeError(identifier, dataType, node, source);
        }
    }

    visitor::nodes::ArrayDeclarationNode Arrays::analyzeArrayDeclaration(visitor::nodes::ArrayDeclarationNode& node, const std::string& source) {
        const auto items = node.elements;

        if (const int length = items.size(); node.size != "auto" && length > std::stoi(node.size)) {
            utils::Errors::throwRangeError("Expected array size of " + node.size + ", but received " + std::to_string(length) + " elements.", node, source);
        }

        for (const auto& item : items) {
            const auto [itemType, itemValue, itemNode] = utils::Helpers::resolveItem(item.value);

            analyzeUnOrSingedInteger(node.type, itemValue, node.identifier, itemType, node, source);
            checkNumberRange(node.type, itemValue, node, source);
            analyzeArrayItems(node.identifier, node.type, itemValue, item.type, itemNode, source);
        }

        return node;
    }

    void Arrays::checkNumberRange(const std::string& dataType, const std::string& rValue, const std::any& node, const std::string& source) {
        // Signed Integer
        // =======================================================================================================================================
        if (dataType == "int8") {
            if (!utils::Helpers::fitsInInteger(rValue, 8)) {
                utils::Errors::throwRangeError("Value exceeds 8-bit signed integer range", node, source);
            }
        }

        if (dataType == "int" || dataType == "int32") {
            if (!utils::Helpers::fitsInInteger(rValue, 32)) {
                utils::Errors::throwRangeError("Value exceeds 32-bit signed integer range", node, source);
            }
        }

        if (dataType == "int64") {
            if (!utils::Helpers::fitsInInteger(rValue, 64)) {
                utils::Errors::throwRangeError("Value exceeds 128-bit signed integer range", node, source);
            }
        }

        // Unsigned Integer
        // =======================================================================================================================================
        if (dataType == "uint8") {
            if (!utils::Helpers::fitsInInteger(rValue, 8) && utils::Helpers::parseFloat(rValue) < 0) {
                utils::Errors::throwRangeError("Value exceeds 8-bit unsigned integer range", node, source);
            }
        }

        if (dataType == "uint" || dataType == "uint32") {
            if (!utils::Helpers::fitsInInteger(rValue, 32) && utils::Helpers::parseFloat(rValue) < 0) {
                utils::Errors::throwRangeError("Value exceeds 32-bit unsigned integer range", node, source);
            }
        }

        if (dataType == "uint64") {
            if (!utils::Helpers::fitsInInteger(rValue, 64) && utils::Helpers::parseFloat(rValue) < 0) {
                utils::Errors::throwRangeError("Value exceeds 64-bit unsigned integer range", node, source);
            }
        }

        // Float
        if (dataType == "float" || dataType == "float32") {
            if (!utils::Helpers::fitsInInteger(rValue, 32)) {
                utils::Errors::throwRangeError("Value exceeds 32-bit float range", node, source);
            }
        }

        if (dataType == "float64") {
            if (!utils::Helpers::fitsInInteger(rValue, 64)) {
                utils::Errors::throwRangeError("Value exceeds 64-bit float range", node, source);
            }
        }
    }

    void Arrays::analyzeArrayItems(const std::string& identifier, const std::string& returnType, const std::string& rValue, const std::string& dataType, const std::any& node, const std::string& source) {
        analyze64BitInteger(rValue, dataType, identifier, source, node);

        if (dataType.starts_with("uint")) {
            analyzeUnsignedInteger(rValue, dataType, identifier, source, node);

        } else if (dataType.starts_with("int")) {
            analyzeSignedInteger(rValue, dataType, identifier, source, node);

        } else if (dataType.starts_with("float")) {
            analyzeFloat(rValue, dataType, source, node);

        } else if (dataType == "str" && returnType != "str") {
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        } else if (dataType == "bool" && returnType != "bool") {
            utils::Errors::throwTypeError(identifier, dataType, node, source);
        }
    }

    void Arrays::processArrayItems(const std::string& identifier, const std::string& arrayType, std::string& itemType, std::any& itemValue, std::string& boolValue, std::string& rValue, const std::any& itemResult, const std::string& source) {
        const auto [type, value, node] = utils::Helpers::resolveItem(itemResult);

        itemType = type;
        rValue = value;
        itemValue = node;

        if (itemType == "bool")
            boolValue = value;

        // 🔒 Single, correct validation point
        if (!checkArrayDataType(arrayType, itemType, rValue)) {
            utils::Errors::throwTypeError(identifier, arrayType, itemResult, source);
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
            if (const auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), v); ec != std::errc() || ptr != value.data() + value.size())
                return false;

            const int bits = bitWidth(dataType);
            const long long min = -(1LL << (bits - 1));

            if (const long long max = (1LL << (bits - 1)) - 1; v < min || v > max)
                return false;

            // conversion rules
            return isIntType(returnType) || isUIntType(returnType) || isFloatType(returnType);
        }

        // -------------------------------
        // UNSIGNED INTEGER
        // -------------------------------
        if (isUIntType(dataType)) {
            unsigned long long v{};
            if (auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), v); ec != std::errc() || ptr != value.data() + value.size())
                return false;

            const int bits = bitWidth(dataType);

            if (const unsigned long long max = bits == 64 ? std::numeric_limits<unsigned long long>::max() : (1ULL << bits) - 1; v > max)
                return false;

            return returnType == "int" || isFloatType(returnType);
        }

        // -------------------------------
        // FLOAT
        // -------------------------------
        if (isFloatType(dataType)) {
            try {
                const long double v = std::stold(value);
                (void)v; // value parsed successfully
            } catch (...) {
                return false;
            }

            return isFloatType(returnType) || returnType == "int";
        }

        return false;
    }

} // namespace yogi::semantic