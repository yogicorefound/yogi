//
// Created by Brayhan De Aza on 5/1/26.
//

#pragma once

#include "utils/utils.h"

namespace yogi::semantic {
    struct IntegerRange {
        long long min;
        long long max;
    };

    struct UnsignedIntegerRange {
        unsigned long long min;
        unsigned long long max;
    };

    inline bool isNumeric(const utils::Types t) {
        return t >= utils::Types::Integer8 && t <= utils::Types::Double;
    }

    inline  bool isUnsigned(const utils::Types t) {
        return t == utils::Types::UnsignedInteger8 ||t == utils::Types::UnsignedInteger16 || t == utils::Types::UnsignedInteger32 || t == utils::Types::UnsignedInteger64;
    }

    inline  bool isSigned(const utils::Types t) {
        return !isUnsigned(t) && t != utils::Types::Float && t != utils::Types::Double && t != utils::Types::Boolean && t != utils::Types::String && t != utils::Types::Void;
    }

    inline bool isInteger(const utils::Types t) {
        return t == utils::Types::Integer8 || t == utils::Types::Integer16 || t == utils::Types::Integer32 || t == utils::Types::Integer64;
    }

    inline IntegerRange getSignedIntegerRange(const utils::Types& type) {
        switch (type) {
            case utils::Types::Integer8:  return {-128, 127};
            case utils::Types::Integer16: return {-32768, 32767};
            case utils::Types::Integer32: return {-2147483648LL, 2147483647LL};
            case utils::Types::Integer64: return {
                -9223372036854775807LL - 1,
                 9223372036854775807LL
            };

            default: return {0, 0};
        }
    }

    inline UnsignedIntegerRange getUnsignedRange(utils::Types t) {
        switch (t) {
            case utils::Types::UnsignedInteger8:  return {0, 255};
            case utils::Types::UnsignedInteger16: return {0, 65535};
            case utils::Types::UnsignedInteger32: return {0, 4294967295ULL};
            case utils::Types::UnsignedInteger64: return {0, 18446744073709551615ULL};

            default: return {0, 0};
        }
    }

    inline void validateIntegerLiteral(const long long value, const utils::Types& targetType, const std::any& node, const std::string& source) {
        if (const auto [min, max] = getSignedIntegerRange(targetType); value < min || value > max) {
            utils::Errors::throwRangeError("Integer literal out of range", node, source);

        }
    }

    inline  utils::Types inferIntegerType(const long long value) {
        if (value >= -128 && value <= 127) return utils::Types::Integer8;
        if (value >= -32768 && value <= 32767) return utils::Types::Integer16;
        if (value >= -2147483648LL && value <= 2147483647LL) return utils::Types::Integer32;

        return utils::Types::Integer64;
    }

    inline  utils::Types promoteInteger(utils::Types a, utils::Types b) {
        auto rank = [](utils::Types t) -> int {
            switch (t) {
                case utils::Types::Integer8: return 1;
                case utils::Types::Integer16: return 2;
                case utils::Types::Integer32: return 3;
                case utils::Types::Integer64: return 4;

                case utils::Types::UnsignedInteger8: return 1;
                case utils::Types::UnsignedInteger16: return 2;
                case utils::Types::UnsignedInteger32: return 3;
                case utils::Types::UnsignedInteger64: return 4;

                default: return 0;
            }
        };

        const bool aUnsigned = isUnsigned(a);
        const bool bUnsigned = isUnsigned(b);

        // same signedness → simple max rank
        if (aUnsigned == bUnsigned) {
            return rank(a) >= rank(b) ? a : b;
        }

        // mixed signed/unsigned → promote to next safe signed type
        return utils::Types::Integer64; // safe fallback (you can refine later)
    }

    inline  bool fitsInRange(const long long value, const utils::Types type) {
        if (isUnsigned(type)) {
            auto r = getUnsignedRange(type);
            return value >= 0 && static_cast<unsigned long long>(value) <= r.max;
        }

        const auto [min, max] = getSignedIntegerRange(type);
        return value >= min && value <= max;
    }

    inline utils::Types resolveNumericResultType(utils::Types a, utils::Types b) {
        auto rank = [](utils::Types t) -> int {
            switch (t) {
                case utils::Types::Integer8:
                case utils::Types::UnsignedInteger8: return 1;

                case utils::Types::Integer16:
                case utils::Types::UnsignedInteger16: return 2;

                case utils::Types::Integer32:
                case utils::Types::UnsignedInteger32: return 3;

                case utils::Types::Integer64:
                case utils::Types::UnsignedInteger64: return 4;

                case utils::Types::Float: return 5;
                case utils::Types::Double: return 6;

                default: return 0;
            }
        };

        // float dominance
        if (a == utils::Types::Double || b == utils::Types::Double)
            return utils::Types::Double;

        if (a == utils::Types::Float || b == utils::Types::Float)
            return utils::Types::Float;

        // integer promotion
        return rank(a) >= rank(b) ? a : b;
    }

    inline utils::Types getVariableDeclarationType(const std::string& type) {
        if (type == "int8") return utils::Types::Integer8;
        if (type == "int16") return utils::Types::Integer16;
        if (type == "int32") return utils::Types::Integer32;
        if (type == "int") return utils::Types::Integer32;
        if (type == "int64") return utils::Types::Integer64;

        if (type == "uint8") return utils::Types::UnsignedInteger8;
        if (type == "uint16") return utils::Types::UnsignedInteger16;
        if (type == "uint32") return utils::Types::UnsignedInteger32;
        if (type == "uint") return utils::Types::UnsignedInteger32;
        if (type == "uint64") return utils::Types::UnsignedInteger64;

        if (type == "float") return utils::Types::Float;
        if (type == "double") return utils::Types::Double;
        if (type == "bool") return utils::Types::Boolean;
        if (type == "string") return utils::Types::String;

        return utils::Types::None;
    }

    inline std::string convertTypeToString(const utils::Types type) {
        if (type == utils::Types::Integer8) return "int8";
        if (type == utils::Types::Integer16) return "int16";
        if (type == utils::Types::Integer32) return "int32";
        if (type == utils::Types::Integer64) return "int64";

        if (type == utils::Types::UnsignedInteger8) return "uint8";
        if (type == utils::Types::UnsignedInteger16) return "uint16";
        if (type == utils::Types::UnsignedInteger32) return "uint32";
        if (type == utils::Types::UnsignedInteger64) return "uint64";

        if (type == utils::Types::Float) return "float";
        if (type == utils::Types::Double) return "double";
        if (type == utils::Types::Boolean) return "boolean";
        if (type == utils::Types::String) return "string";

        return "";
    }
}
