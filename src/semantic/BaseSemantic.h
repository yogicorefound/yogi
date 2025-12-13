//
// Created by Brayhan De Aza on 11/27/25.
//

#ifndef CROMIO_BASE_SEMANTIC_H
#define CROMIO_BASE_SEMANTIC_H

#include <any>
#include <string>

namespace cromio::semantic {
    class BaseSemantic {
       public:
        static const std::string INT64_MAX_STR;
        static const std::string INT64_MIN_STR;
        static const std::string UINT64_MAX_STR;
        static const std::string FLOAT32_MAX_STR;
        static const std::string FLOAT32_MIN_STR;
        static const std::string FLOAT64_MAX_STR;
        static const std::string FLOAT64_MIN_STR;

        static bool checkDataType(const std::string& dataType, const std::string& returnType);

        static void analyzeSignedInteger(const std::string& rValue, const std::string& dataType, const std::string& identifier, const std::string& source, const std::any& node);

        static void analyzeUnsignedInteger(const std::string& rValue, const std::string& dataType, const std::string& identifier, const std::string& source, const std::any& node);

        static void analyzeFloat(const std::string& rValue, const std::string& dataType, const std::string& source, const std::any& node);

        static void analyze64BitInteger(const std::string& rValue, const std::string& dataType, const std::string& identifier, const std::string& source, const std::any& node);
    };
} // namespace cromio::semantic

#endif // CROMIO_BASE_SEMANTIC_H