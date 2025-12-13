//
// Created by Brayhan De Aza on 12/2/25.
//

#include "semantic/variables/Variables.h"
#include <ast/nodes/nodes.h>
#include <string>
#include <unordered_set>
#include "semantic/BaseSemantic.h"
#include "utils/utils.h"

namespace cromio::semantic {
    using namespace cromio::visitor::nodes;

    void Variables::analyzeVariableWithoutAssignment(const VariableDeclarationNode& node, const Position& start, const Position& end) {
        const std::string& type = node.varType;

        // Create a copy of the node to modify
        VariableDeclarationNode result = node;

        if (type.find("int") != std::string::npos) {
            auto value = IntegerLiteralNode("0", start, end);
            result.value = std::any(value);

        } else if (type.find("float") != std::string::npos) {
            auto value = FloatLiteralNode("0.0", start, end);
            result.value = std::any(value);

        } else if (type.find("str") != std::string::npos) {
            auto value = StringLiteralNode("", start, end);
            result.value = std::any(value);

        } else if (type.find("bool") != std::string::npos) {
            auto value = BooleanLiteralNode("0", start, end);
            result.value = std::any(value);
        }
    }

    void Variables::analyzeVariableDeclaration(const VariableDeclarationNode& node, const std::string& source) {
        const std::string& identifier = node.identifier;
        const std::string& dataType = node.varType;

        // Extract value information from the node
        if (!node.value.has_value()) {
            throw std::runtime_error("Variable declaration missing value: " + identifier);
        }

        std::string returnType;
        std::string rValue;
        std::string stringValue;

        // Determine the type and value from the std::any
        try {
            if (node.value.type() == typeid(IntegerLiteralNode)) {
                auto val = std::any_cast<IntegerLiteralNode>(node.value);
                returnType = "int";
                rValue = val.value;
                stringValue = val.value;
            } else if (node.value.type() == typeid(FloatLiteralNode)) {
                auto val = std::any_cast<FloatLiteralNode>(node.value);
                returnType = "float";
                rValue = val.value;
                stringValue = val.value;
            } else if (node.value.type() == typeid(BooleanLiteralNode)) {
                auto val = std::any_cast<BooleanLiteralNode>(node.value);
                returnType = "bool";
                rValue = val.value;
                stringValue = (val.value == "1") ? "true" : "false";
            } else if (node.value.type() == typeid(StringLiteralNode)) {
                auto val = std::any_cast<StringLiteralNode>(node.value);
                returnType = "str";
                rValue = val.value;
                stringValue = val.value;
            } else if (node.value.type() == typeid(BinaryExpressionNode)) {
                auto val = std::any_cast<BinaryExpressionNode>(node.value);
                returnType = val.resultType;
                rValue = val.value;
                stringValue = val.value;
            } else if (node.value.type() == typeid(NoneLiteralNode)) {
                auto val = std::any_cast<NoneLiteralNode>(node.value);
                returnType = "none";
                rValue = "0";
                stringValue = "None";
            } else {
                throw std::runtime_error("Unsupported value type in variable declaration");
            }
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Failed to cast variable value: " + std::string(e.what()));
        }

        // Type checking
        if (!checkDataType(dataType, returnType)) {
            utils::Errors::throwTypeError(identifier, dataType, node.value, source);
        }

        // Range checking for integers
        analyze64BitInteger(rValue, dataType, identifier, source, node.value);

        if (dataType.find("uint") != std::string::npos) {
            analyzeUnsignedInteger(rValue, dataType, identifier, source, node.value);
        } else if (dataType.find("int") != std::string::npos) {
            analyzeSignedInteger(rValue, dataType, identifier, source, node.value);
        } else if (dataType.find("float") != std::string::npos) {
            analyzeFloat(rValue, dataType, source, node.value);
        } else if (dataType == "str" && returnType != "str") {
            utils::Errors::throwTypeError(identifier, dataType, node.value, source);
        } else if (dataType == "bool") {
            if (stringValue != "true" && stringValue != "false") {
                utils::Errors::throwTypeError(identifier, dataType, node.value, source);
            }
        }

        // Create result node with normalized value
        VariableDeclarationNode result = node;

        // Normalize integer values
        if (dataType.find("uint") != std::string::npos || dataType.find("int") != std::string::npos) {
            long long normalizedValue = std::stoll(rValue);
            result.value = std::any(IntegerLiteralNode(std::to_string(normalizedValue), node.start, node.end));
        }

        // Normalize float values
        if (dataType.find("float") != std::string::npos) {
            float normalizedValue = std::stof(rValue);
            result.value = std::any(FloatLiteralNode(std::to_string(normalizedValue), node.start, node.end));
        }
    }
    void Variables::analyzeVariableReassignment(const VariableDeclarationNode& node, const std::string& source) {
        std::string identifier = node.identifier;
        std::string returnType;
        std::string rValue;
        std::string boolValue;

        // Determine the type and value from the std::any
        try {
            if (node.value.type() == typeid(IntegerLiteralNode)) {
                auto val = std::any_cast<IntegerLiteralNode>(node.value);
                returnType = "int";
                rValue = val.value;

            } else if (node.value.type() == typeid(FloatLiteralNode)) {
                auto val = std::any_cast<FloatLiteralNode>(node.value);
                returnType = "float";
                rValue = val.value;
            } else if (node.value.type() == typeid(BooleanLiteralNode)) {
                auto val = std::any_cast<BooleanLiteralNode>(node.value);
                returnType = "bool";
                rValue = val.value;
                boolValue = (val.value == "1") ? "true" : "false";
            } else if (node.value.type() == typeid(StringLiteralNode)) {
                auto val = std::any_cast<StringLiteralNode>(node.value);
                returnType = "str";
                rValue = val.value;
            } else if (node.value.type() == typeid(BinaryExpressionNode)) {
                auto val = std::any_cast<BinaryExpressionNode>(node.value);
                returnType = val.resultType;
                rValue = val.value;
            } else if (node.value.type() == typeid(NoneLiteralNode)) {
                auto val = std::any_cast<NoneLiteralNode>(node.value);
                returnType = "none";
                rValue = "0";
            } else {
                throw std::runtime_error("Unsupported value type in variable declaration");
            }

        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Failed to cast variable value: " + std::string(e.what()));
        }

        // Type checking - ensure new value matches variable's declared type
        if (!checkDataType(node.varType, returnType)) {
            utils::Errors::throwTypeError(identifier, node.varType, node, source);
        }

        // Range checking for integers
        analyze64BitInteger(rValue, node.varType, identifier, source, node.value);

        if (node.varType.find("uint") != std::string::npos) {
            analyzeUnsignedInteger(rValue, node.varType, identifier, source, node.value);
        } else if (node.varType.find("int") != std::string::npos) {
            analyzeSignedInteger(rValue, node.varType, identifier, source, node.value);
        } else if (node.varType.find("float") != std::string::npos) {
            analyzeFloat(rValue, node.varType, source, node.value);
        } else if (node.varType == "str" && returnType != "str") {
            utils::Errors::throwTypeError(identifier, node.varType, node.value, source);
        } else if (node.varType == "bool") {
            if (boolValue != "true" && boolValue != "false") {
                utils::Errors::throwTypeError(identifier, node.varType, node.value, source);
            }
        }
    }
    bool Variables::checkDataType(const std::string& dataType, const std::string& returnType) {
        if (dataType == "int" || dataType == "int8" || dataType == "int16" || dataType == "int32" || dataType == "int64") {
            return returnType == "int" || returnType == "float";
        }

        if (dataType == "uint" || dataType == "uint8" || dataType == "uint16" || dataType == "uint32" || dataType == "uint64") {
            return returnType == "int" || returnType == "float";
        }

        if (dataType == "float" || dataType == "float32" || dataType == "float64") {
            return returnType == "float" || returnType == "int";
        }

        if (dataType == "bool") {
            return returnType == "bool";
        }

        if (dataType == "str") {
            return returnType == "str";
        }

        return false;
    }

} // namespace cromio::semantic