//
// Created by Brayhan De Aza on 12/21/25.
//

#include "math.h"
#include <algorithm>
#include <cmath>
#include <string>
#include "antlr4-runtime.h"

namespace cromio::utils::helpers {
    bool Math::strGreater(const std::string& a, const std::string& b) {
        return a.compare(b) > 0;
    }

    bool Math::exceedsUInt64(const std::string& raw) {
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

    Math::DecimalInteger Math::parseDecimalInteger(const std::string& literal) {
        DecimalInteger out;

        std::string s = literal;
        bool negative = false;

        if (!s.empty() && s[0] == '-') {
            negative = true;
            s = s.substr(1);
        }

        size_t ePos = s.find_first_of("eE");
        if (ePos != std::string::npos) {
            out.mantissa = s.substr(0, ePos);
            out.exponent = std::stoi(s.substr(ePos + 1));
        } else {
            out.mantissa = s;
            out.exponent = 0;
        }

        // eliminar ceros a la izquierda
        out.mantissa.erase(0, out.mantissa.find_first_not_of('0'));
        if (out.mantissa.empty())
            out.mantissa = "0";

        if (negative)
            out.mantissa = "-" + out.mantissa;

        return out;
    }

    int Math::effectiveExponent(const DecimalInteger& v) {
        if (v.mantissa == "0")
            return 0;
        return v.exponent + static_cast<int>(v.mantissa.size()) - 1;
    }

    bool Math::fitsInInteger(const std::string& numLiteral, int bitSize) {
        const DecimalInteger v = parseDecimalInteger(numLiteral);

        if (bitSize != 8 && bitSize != 16 && bitSize != 32 && bitSize != 64) {
            throw std::invalid_argument("Unsupported bit size");
        }

        int64_t maxVal = getSignedMax(bitSize);
        int64_t minVal = getSignedMin(bitSize);

        // calcular exponente efectivo
        int effExp = effectiveExponent(v);

        // exponente máximo del número límite
        int64_t absMax = std::abs(maxVal);
        int expMax = static_cast<int>(std::to_string(absMax).size() - 1);

        if (v.mantissa[0] == '-') {
            // número negativo
            if (effExp > expMax)
                return false;
            if (effExp < expMax)
                return true;

            // effExp == expMax → comparar mantissa
            std::string lhs = v.mantissa.substr(1); // eliminar signo
            std::string rhs = std::to_string(std::abs(minVal));
            if (lhs.size() < rhs.size())
                lhs.append(rhs.size() - lhs.size(), '0');
            else if (rhs.size() < lhs.size())
                rhs.append(lhs.size() - rhs.size(), '0');

            return lhs <= rhs;
        } else {
            // número positivo
            if (effExp > expMax)
                return false;
            if (effExp < expMax)
                return true;

            std::string lhs = v.mantissa;
            std::string rhs = std::to_string(maxVal);

            if (lhs.size() < rhs.size())
                lhs.append(rhs.size() - lhs.size(), '0');
            else if (rhs.size() < lhs.size())
                rhs.append(lhs.size() - rhs.size(), '0');

            return lhs <= rhs;
        }
    }

    bool Math::fitsInInt32(const std::string& literal) {
        const DecimalInteger v = parseDecimalInteger(literal); // parsea mantissa + exponent

        // calcular exponente efectivo
        const int effExp = effectiveExponent(v);

        // int32 máximo ≈ 2.147483647e9 → exponente efectivo = 9
        constexpr int MAX_EFFECTIVE_EXP = 9;

        if (!v.mantissa.empty() && v.mantissa[0] == '-') {
            // número negativo → debe ser >= INT32_MIN
            return effExp <= MAX_EFFECTIVE_EXP;
        }
        return effExp <= MAX_EFFECTIVE_EXP;
    }

    bool Math::fitsInInt64(const std::string& literal) {
        DecimalInteger v = parseDecimalInteger(literal); // parsea mantissa + exponent

        // Calcular exponente efectivo
        int effExp = effectiveExponent(v);

        // int64 máximo ≈ 9.223372036854775807e18 → exponente efectivo = 18
        constexpr int MAX_EFFECTIVE_EXP = 18;

        if (v.mantissa[0] == '-') {
            // número negativo → debe ser >= INT64_MIN
            return effExp <= MAX_EFFECTIVE_EXP; // ajustable según mantissa
        }

        return effExp <= MAX_EFFECTIVE_EXP;
    }

    bool Math::exceedsInt64(const std::string& raw, const bool isUnsigned) {
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

    bool Math::isGreaterUnsigned(const std::string& num, const std::string& max) {
        // 1️⃣ Quitar ceros a la izquierda
        auto normalize = [](const std::string& s) -> std::string {
            const size_t pos = s.find_first_not_of('0');
            if (pos == std::string::npos)
                return "0";
            return s.substr(pos);
        };

        std::string a = normalize(num);
        std::string b = normalize(max);

        // 2️⃣ Comparar longitud
        if (a.size() != b.size())
            return a.size() > b.size();

        // 3️⃣ Comparación lexicográfica (segura para decimal)
        return a > b;
    }

    bool Math::isGreaterSigned(const std::string& num, const std::string& maxPos, const std::string& maxNeg) {
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

    bool Math::isInteger(const double number) {
        double intPart;
        return std::modf(number, &intPart) == 0.0;
    }

    bool Math::isValidNumber(const std::string& str) {
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

    std::string Math::trimLeadingZeros(const std::string& s) {
        size_t i = 0;
        while (i < s.size() && s[i] == '0')
            i++;
        return s.substr(i);
    }

    bool Math::isAbsGreaterThan(const DecimalFloat& v, const std::string& maxMantissa, const int maxExponent) {
        if (v.exponent != maxExponent)
            return v.exponent > maxExponent;

        if (v.mantissa.size() != maxMantissa.size())
            return v.mantissa.size() > maxMantissa.size();

        return v.mantissa > maxMantissa;
    }

    bool Math::fitsInFloat32(const std::string& literal) {
        DecimalFloat v = parseDecimalFloat(literal);

        // float32 max: 3.402823466e38
        constexpr int MAX_EFFECTIVE_EXP = 38;
        const std::string MAX_MANTISSA = "3402823466"; // 10-digit mantissa

        int effExp = v.exponent + static_cast<int>(v.mantissa.size()) - 1;

        if (effExp < MAX_EFFECTIVE_EXP)
            return true; // seguro que cabe

        if (effExp > MAX_EFFECTIVE_EXP)
            return false; // seguro que NO cabe

        // effExp == MAX_EFFECTIVE_EXP → comparar mantissa lexicográficamente
        std::string lhs = v.mantissa;
        std::string rhs = MAX_MANTISSA;

        // pad con ceros a la derecha para tener mismo tamaño
        if (lhs.size() < rhs.size())
            lhs.append(rhs.size() - lhs.size(), '0');
        else if (rhs.size() < lhs.size())
            rhs.append(lhs.size() - rhs.size(), '0');

        return lhs <= rhs; // verdadero solo si no supera el máximo
    }

    bool Math::fitsInFloat64(const std::string& literal) {
        DecimalFloat v = parseDecimalFloat(literal);

        // float64 max exponent ≈ 308 (1.7976931348623157e+308)
        constexpr int MAX_EFFECTIVE_EXP = 308;

        int effExp = v.exponent + static_cast<int>(v.mantissa.size()) - 1;

        return effExp <= MAX_EFFECTIVE_EXP;
    }

    Math::DecimalFloat Math::parseDecimalFloat(const std::string& s) {
        DecimalFloat out{};
        size_t i = 0;

        out.negative = s[i] == '-';
        if (s[i] == '+' || s[i] == '-')
            i++;

        std::string intPart, fracPart;
        while (i < s.size() && isdigit(s[i]))
            intPart += s[i++];

        if (i < s.size() && s[i] == '.') {
            i++;
            while (i < s.size() && isdigit(s[i]))
                fracPart += s[i++];
        }

        int exp = 0;
        if (i < s.size() && (s[i] == 'e' || s[i] == 'E')) {
            i++;
            int sign = 1;
            if (s[i] == '+' || s[i] == '-') {
                sign = s[i] == '-' ? -1 : 1;
                i++;
            }
            while (i < s.size() && isdigit(s[i]))
                exp = exp * 10 + (s[i++] - '0');
            exp *= sign;
        }

        out.mantissa = intPart + fracPart;
        out.exponent = exp - static_cast<int>(fracPart.size());

        // remove leading zeros
        size_t pos = out.mantissa.find_first_not_of('0');
        out.mantissa = pos == std::string::npos ? "0" : out.mantissa.substr(pos);

        return out;
    }

    bool Math::isGreaterThanFloatMax(const std::string& literal) {
        if (literal.starts_with('-'))
            return false; // negative never overflows max

        const DecimalFloat v = parseDecimalFloat(literal);

        // FLOAT_MAX = 3.402823466e+38
        const std::string maxMantissa = "3402823466";

        if (constexpr int maxExponent = 29; v.exponent != maxExponent)
            return v.exponent > maxExponent;

        if (v.mantissa.size() != maxMantissa.size())
            return v.mantissa.size() > maxMantissa.size();

        return v.mantissa > maxMantissa;
    }

    bool Math::isLessThanFloatMin(const std::string& literal) {
        if (literal.empty() || literal[0] != '-')
            return false;

        DecimalFloat v = parseDecimalFloat(literal);

        // float max magnitude = 3.402823466e+38
        static const std::string MAX_MANTISSA = "3402823466";
        static constexpr int MAX_EXPONENT = 29;

        // Compare absolute value
        if (v.exponent != MAX_EXPONENT)
            return v.exponent > MAX_EXPONENT;

        if (v.mantissa.size() != MAX_MANTISSA.size())
            return v.mantissa.size() > MAX_MANTISSA.size();

        return v.mantissa > MAX_MANTISSA;
    }

} // namespace cromio::utils::helpers