//
// Created by Brayhan De Aza on 12/2/25.
//

#include "Arrays.h"
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

    bool Arrays::checkArrayDataType(const std::string& dataType, const std::string& returnType) {
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