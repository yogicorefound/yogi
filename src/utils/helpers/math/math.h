//
// Created by Brayhan De Aza on 12/21/25.
//

#pragma once

#include <any>
#include <string>
#include <stdexcept>

namespace cromio::utils::helpers {
    class Math {
       public:
        static std::string trimLeadingZeros(const std::string& s);
        static bool exceedsInt64(const std::string& raw, bool isUnsigned);
        static bool exceedsUInt64(const std::string& raw);
        static bool strGreater(const std::string& a, const std::string& b);
        static bool isGreaterUnsigned(const std::string& num, const std::string& max);
        static bool isGreaterSigned(const std::string& num, const std::string& maxPos, const std::string& maxNeg);
        static bool isValidNumber(const std::string& str);
        static bool isInteger(double number);

        struct DecimalInteger {
            std::string mantissa; // sin ceros a la izquierda
            int exponent; // para notación exponencial
        };

        struct DecimalFloat {
            bool negative;
            std::string mantissa; // digits only
            int exponent; // base-10 exponent
        };

        static DecimalFloat parseDecimalFloat(const std::string& s);
        static bool isGreaterThanFloatMax(const std::string&);
        static bool isLessThanFloatMin(const std::string& literal);
        static bool isAbsGreaterThan(const DecimalFloat& v, const std::string& maxMantissa, int maxExponent);
        static int effectiveExponent(const DecimalInteger& v);
        static DecimalInteger parseDecimalInteger(const std::string& literal);

        static bool fitsInFloat32(const std::string& literal);
        static bool fitsInFloat64(const std::string& literal);
        static bool fitsInInt32(const std::string& literal);
        static bool fitsInInt64(const std::string& literal);
        static bool fitsInInteger(const std::string& numLiteral, int bitSize);

        struct ResolvedItem {
            std::string type;
            std::string value;
            std::any node;
        };

        // Límites signed por bit size
        static int64_t getSignedMax(int bitSize) {
            switch (bitSize) {
                case 8:
                    return 127;
                case 16:
                    return 32767;
                case 32:
                    return 2147483647;
                case 64:
                    return 9223372036854775807LL;
                default:
                    throw std::invalid_argument("Unsupported bit size");
            }
        }

        static int64_t getSignedMin(int bitSize) {
            switch (bitSize) {
                case 8:
                    return -128;
                case 16:
                    return -32768;
                case 32:
                    return -2147483648;
                case 64:
                    return -9223372036854775807LL - 1;
                default:
                    throw std::invalid_argument("Unsupported bit size");
            }
        }
    };
} // namespace cromio::utils::helpers