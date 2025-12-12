//
// Created by Brayhan De Aza on 12/2/25.
//

#include "semantic/variables/Variables.h"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_set>
#include "semantic/BaseSemantic.h"

namespace cromio::semantic {

    json Variables::cleanASTExpression(const json& node) {
        if (!node.is_object())
            return node;

        // Detecta si el nodo es un literal por su "kind"
        bool isLiteral = false;
        if (node.contains("kind") && node["kind"].is_string()) {
            if (const auto k = node["kind"].get<std::string>(); k.size() >= 7 && k.substr(k.size() - 7) == "Literal") {
                isLiteral = true;
            }
        }

        json cleaned = json::object();

        static const std::unordered_set<std::string> removeKeys = {"raw", "value", "stringValue", "numberValue"};

        for (auto it = node.begin(); it != node.end(); ++it) {
            const std::string& key = it.key();
            const json& value = it.value();

            if (value.is_object() || value.is_array()) {
                cleaned[key] = cleanASTExpression(value);
                continue;
            }

            // --- LITERALS ---
            if (isLiteral) {
                if (key == "raw" || key == "value" || key == "kind") {
                    cleaned[key] = value;
                }
                continue;
            }

            // --- NO LITERALS ---
            if (!removeKeys.contains(key)) {
                cleaned[key] = value;
            }
        }

        return cleaned;
    }

    json Variables::analyzeVariableWithoutAssignment(json& node, const antlr4::Token* start, const antlr4::Token* stop) {
        const std::string type = node["DataType"]["value"];

        if (type.contains("int")) {
            json value = utils::Helpers::createNode("", "IntegerLiteral", start, stop);
            value["value"] = 0;
            value["raw"] = "0";
            value["type"] = "int";
            value["stringValue"] = "0";
            value["numberValue"] = "0";
            node["value"] = value;

            return node;
        }
        if (type.contains("float")) {
            json value = utils::Helpers::createNode("", "FloatLiteral", start, stop);
            value["value"] = 0.0;
            value["raw"] = "0.0";
            value["type"] = "float";
            value["stringValue"] = "0.0";
            value["numberValue"] = "0.0";

            node["value"] = value;
            return node;
        }
        if (type.contains("str")) {
            json value = utils::Helpers::createNode("", "StringLiteral", start, stop);
            value["value"] = "";
            value["raw"] = "";
            value["type"] = "str";
            value["stringValue"] = "";
            value["numberValue"] = "";
            node["value"] = value;
            return node;
        }
        if (type.contains("bool")) {
            json value = utils::Helpers::createNode("", "BooleanLiteral", start, stop);
            value["value"] = false;
            value["raw"] = "false";
            value["type"] = "bool";
            value["stringValue"] = "false";
            value["numberValue"] = "0";
            node["value"] = value;
            return node;
        }

        node["value"] = nullptr;
        return node;
    }

    json Variables::analyzeVariableDeclaration(json& node, const std::string& source) {
        if (node["value"].contains("error")) {
            const std::string error = node["value"]["error"];
            utils::Errors::throwError("Error", error, node, source);
        }

        const std::string identifier = node["Identifier"]["value"];
        const std::string dataType = node["DataType"]["value"];
        const std::string rValue = node["value"]["numberValue"];
        const std::string stringValue = node["value"]["stringValue"];
        const std::string returnType = node["value"]["type"];

        if (!checkDataType(dataType, returnType)) {
            utils::Errors::throwTypeError(identifier, dataType, node, source);
        }

        analyze64BitInteger(rValue, dataType, identifier, source, node);

        if (dataType.contains("uint")) {
            analyzeUnsignedInteger(rValue, dataType, identifier, source, node);
        }

        else if (dataType.contains("int")) {
            analyzeSignedInteger(rValue, dataType, identifier, source, node);
        }

        else if (dataType.contains("float")) {
            analyzeFloat(rValue, dataType, source, node);
        }

        else if (dataType == "str" && returnType != "str") {
            utils::Errors::throwTypeError(identifier, dataType, node, source);
        }

        else if (dataType == "bool") {
            if (stringValue != "true" && stringValue != "false") {
                utils::Errors::throwTypeError(identifier, dataType, node, source);
            }
        }

        if (dataType.contains("uint") || dataType.contains("int")) {
            node["value"]["raw"] = std::to_string(std::stoll(rValue));
            node["value"]["value"] = std::stoll(rValue);
            node["value"]["type"] = "int";
            node["value"]["stringValue"] = std::to_string(std::stoll(rValue));
            node["value"]["numberValue"] = std::to_string(std::stoll(rValue));
        }

        if (dataType.contains("float")) {
            node["value"]["raw"] = std::to_string(std::stof(rValue));
            node["value"]["value"] = std::stof(rValue);
            node["value"]["type"] = "float";
            node["value"]["stringValue"] = std::to_string(std::stof(rValue));
            node["value"]["numberValue"] = std::to_string(std::stof(rValue));
        }

        return node;
    }

    bool Variables::checkDataType(const std::string& dataType, const std::string& returnType) {
        if (dataType == "int" || dataType == "int8" || dataType == "int16" || dataType == "int32" || dataType == "int64") {
            if (returnType == "int" || returnType == "float")
                return true;

            return false;
        }

        if (dataType == "uint" || dataType == "uint8" || dataType == "uint16" || dataType == "uint32" || dataType == "uint64") {
            if (returnType == "int" || returnType == "float")
                return true;

            return false;
        }

        if (dataType == "float" || dataType == "float32" || dataType == "float64") {
            if (returnType == "float" || returnType == "int")
                return true;

            return false;
        }

        if (dataType == "bool") {
            if (returnType == "bool")
                return true;

            return false;
        }

        if (dataType == "str") {
            if (returnType == "str")
                return true;

            return false;
        }

        return false;
    }

} // namespace cromio::semantic