//
// Created by Brayhan De Aza on 12/7/25.
//

#include "BaseSemantic.h"
#include <cstdint>
#include <string>
#include "utils/utils.h"

namespace cromio::semantic {
    const std::string BaseSemantic::INT64_MAX_STR = "9223372036854775807";
    const std::string BaseSemantic::INT64_MIN_STR = "9223372036854775808"; // abs value
    const std::string BaseSemantic::UINT64_MAX_STR = "18446744073709551615";
    const std::string BaseSemantic::FLOAT32_MAX_STR = "3.4028235e38";
    const std::string BaseSemantic::FLOAT32_MIN_STR = "-3.4028235e38";
    const std::string BaseSemantic::FLOAT64_MAX_STR = "1.7976931348623157e308";
    const std::string BaseSemantic::FLOAT64_MIN_STR = "-1.7976931348623157e308";

    bool BaseSemantic::checkDataType(const std::string& dataType, const std::string& returnType) {
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

    void BaseSemantic::analyzeSignedInteger(
        const std::string& rValue,
        const std::string& dataType,
        const std::string& identifier,
        const std::string& source,
        const std::any& node) {
        const auto value = utils::Helpers::parseInteger(rValue);
        const bool isValidNumber = utils::Helpers::isValidNumber(std::to_string(value));

        // Validate data type
        if (dataType == "int8" && !isValidNumber)
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        if (dataType == "int16" && !isValidNumber)
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        if ((dataType == "int32" || dataType == "int") && !isValidNumber)
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        // Validate variable value exceeds range
        if (dataType == "int8" && (value < INT8_MIN || value > INT8_MAX))
            utils::Errors::throwRangeError("Value exceeds 8-bit signed integer range", node, source);

        if (dataType == "int16" && (value < INT16_MIN || value > INT16_MAX))
            utils::Errors::throwRangeError("Value exceeds 16-bit signed integer range", node, source);

        std::cout << "Value: " << rValue << std::endl;
        if ((dataType == "int32" || dataType == "int") && !utils::Helpers::fitsInInt32(rValue))
            utils::Errors::throwRangeError("Value exceeds 32-bit signed integer range", node, source);
    }

    void BaseSemantic::analyzeUnsignedInteger(
        const std::string& rValue,
        const std::string& dataType,
        const std::string& identifier,
        const std::string& source,
        const std::any& node) {
        const bool isValidNumber = utils::Helpers::isValidNumber(rValue);
        const auto value = utils::Helpers::parseFloat(rValue);

        // Validate data type
        if (dataType == "uint8" && !isValidNumber)
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        if (dataType == "uint16" && !isValidNumber)
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        if ((dataType == "uint32" || dataType == "uint") && !isValidNumber)
            utils::Errors::throwTypeError(identifier, dataType, node, source);

        // Validate variable value exceeds range
        if (dataType == "uint8" && (value < 0 || value > UINT8_MAX))
            utils::Errors::throwRangeError("Value exceeds 8-bit unsigned integer range", node, source);

        if (dataType == "uint16" && (value < 0 || value > UINT16_MAX))
            utils::Errors::throwRangeError("Value exceeds 16-bit unsigned integer range", node, source);

        if ((dataType == "uint32" || dataType == "uint") && (value < 0 || value > UINT32_MAX))
            utils::Errors::throwRangeError("Value exceeds 32-bit unsigned integer range", node, source);
    }

    void BaseSemantic::analyzeFloat(const std::string& rValue, const std::string& dataType, const std::string& source, const std::any& node) {
        if (dataType == "float" || dataType == "float32") {
            const auto fitIn32 = utils::Helpers::fitsInFloat64(rValue);
            std::cout << "fitIn32: " << fitIn32 << " " << rValue << std::endl;
            if (!utils::Helpers::fitsInFloat32(rValue)) {
                utils::Errors::throwRangeError("<float32> type exceeds 32-bit float range", node, source);
            }

            // if (utils::Helpers::isGreaterSigned(rValue, FLOAT32_MAX_STR, FLOAT32_MIN_STR))
            //     utils::Errors::throwRangeError("<float32> type exceeds 32-bit float range", node, source);
        }

        if (dataType == "float64") {
            const auto fitIn64 = utils::Helpers::fitsInFloat64(rValue);
            std::cout << "fitIn64: " << fitIn64 << std::endl;
            if (!fitIn64) {
                utils::Errors::throwRangeError("<float64> type exceeds 64-bit float range", node, source);
            }

            // if (utils::Helpers::isGreaterSigned(rValue, FLOAT64_MAX_STR, FLOAT64_MIN_STR))
            //     utils::Errors::throwRangeError("<float64> type exceeds 64-bit float range", node, source);
        }
    }

    void BaseSemantic::analyze64BitInteger(
        const std::string& rValue,
        const std::string& dataType,
        const std::string& identifier,
        const std::string& source,
        const std::any& node) {
        const bool isNegative = !rValue.empty() && rValue[0] == '-';

        // ---------------------------------------------
        // SIGNED integers
        // ---------------------------------------------
        if (dataType == "int64") {
            const bool isValidNumber = utils::Helpers::isValidNumber(rValue);
            if (!isValidNumber)
                utils::Errors::throwTypeError(identifier, dataType, node, source);

            if (utils::Helpers::isGreaterSigned(rValue, INT64_MAX_STR, INT64_MIN_STR) || !isValidNumber)
                utils::Errors::throwRangeError("<int64> type exceeds 64-bit range", node, source);
        }

        // ---------------------------------------------
        // UNSIGNED integers
        // ---------------------------------------------
        if (dataType == "uint64") {
            if (const bool isValidNumber = utils::Helpers::isValidNumber(rValue); !isValidNumber)
                utils::Errors::throwTypeError(identifier, dataType, node, source);

            if (isNegative)
                utils::Errors::throwRangeError("<uint64> cannot be negative", node, source);

            if (utils::Helpers::isGreaterUnsigned(rValue, std::to_string(UINT64_MAX)))
                utils::Errors::throwRangeError("<uint64> type exceeds unsigned 64-bit range", node, source);
        }
    }

} // namespace cromio::semantic