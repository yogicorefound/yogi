//
// Created by Brayhan De Aza on 5/1/26.
//

#pragma once

#include "utils/types/Types.h"

namespace yogi::utils {
    class VisitorHelpers {
        public:
            struct IntegerRange {
                long long min;
                long long max;
            };

            struct UnsignedIntegerRange {
                unsigned long long min;
                unsigned long long max;
            };


            static bool isFloat(const Types t) {
                using T = Types;
                return t == T::Float || t == T::Double;
            }

            static bool isNumeric(const Types t) {
                return t >= Types::Integer8 && t <= Types::Double;
            }

            static bool isUnsigned(const Types t) {
                return t == Types::UnsignedInteger8 || t == Types::UnsignedInteger16 || t == Types::UnsignedInteger32 || t == Types::UnsignedInteger64;
            }

            static bool isSigned(const Types t) {
                return !isUnsigned(t) && t != Types::Float && t != Types::Double && t != Types::Boolean &&
                       t != Types::String && t != Types::Void;
            }

            static bool isInteger(const Types t) {
                return t == Types::Integer8 || t == Types::Integer16 || t == Types::Integer32 || t ==
                       Types::Integer64;
            }

            static IntegerRange getSignedIntegerRange(const Types &type) {
                switch (type) {
                    case Types::Integer8: return {-128, 127};
                    case Types::Integer16: return {-32768, 32767};
                    case Types::Integer32: return {-2147483648LL, 2147483647LL};
                    case Types::Integer64: return {
                            -9223372036854775807LL - 1,
                            9223372036854775807LL
                        };

                    default: return {0, 0};
                }
            }

            static UnsignedIntegerRange getUnsignedRange(const Types t) {
                switch (t) {
                    case Types::UnsignedInteger8: return {0, 255};
                    case Types::UnsignedInteger16: return {0, 65535};
                    case Types::UnsignedInteger32: return {0, 4294967295ULL};
                    case Types::UnsignedInteger64: return {0, 18446744073709551615ULL};

                    default: return {0, 0};
                }
            }

            static void validateIntegerLiteral(const long long value, const Types &targetType, const std::any &node, const std::string &source) {
                if (const auto [min, max] = getSignedIntegerRange(targetType); value < min || value > max) {
                    yogi::utils::Errors::throwRangeError("Integer literal out of range", node, source);
                }
            }

            static Types inferIntegerType(const long long value) {
                if (value >= -128 && value <= 127) return Types::Integer8;
                if (value >= -32768 && value <= 32767) return Types::Integer16;
                if (value >= -2147483648LL && value <= 2147483647LL) return Types::Integer32;

                return Types::Integer64;
            }

            static Types promoteInteger(const Types a, const Types b) {
                auto rank = [](const Types t) -> int {
                    switch (t) {
                        case Types::Integer8: return 1;
                        case Types::Integer16: return 2;
                        case Types::Integer32: return 3;
                        case Types::Integer64: return 4;

                        case Types::UnsignedInteger8: return 1;
                        case Types::UnsignedInteger16: return 2;
                        case Types::UnsignedInteger32: return 3;
                        case Types::UnsignedInteger64: return 4;

                        default: return 0;
                    }
                };

                const bool aUnsigned = isUnsigned(a);

                // same signedness → simple max rank
                if (const bool bUnsigned = isUnsigned(b); aUnsigned == bUnsigned) {
                    return rank(a) >= rank(b) ? a : b;
                }

                // mixed signed/unsigned → promote to next safe signed type
                return Types::Integer64; // safe fallback (you can refine later)
            }

            static bool fitsInRange(const long long value, const Types type) {
                if (isUnsigned(type)) {
                    auto [min, max] = getUnsignedRange(type);
                    return value >= 0 && static_cast<unsigned long long>(value) <= max;
                }

                const auto [min, max] = getSignedIntegerRange(type);
                return value >= min && value <= max;
            }

            static Types resolveNumericResultType(const Types a, const Types b) {
                auto rank = [](const Types t) -> int {
                    switch (t) {
                        case Types::Integer8:
                        case Types::UnsignedInteger8: return 1;

                        case Types::Integer16:
                        case Types::UnsignedInteger16: return 2;

                        case Types::Integer32:
                        case Types::UnsignedInteger32: return 3;

                        case Types::Integer64:
                        case Types::UnsignedInteger64: return 4;

                        case Types::Float: return 5;
                        case Types::Double: return 6;

                        default: return 0;
                    }
                };

                // float dominance
                if (a == Types::Double || b == Types::Double)
                    return Types::Double;

                if (a == Types::Float || b == Types::Float)
                    return Types::Float;

                // integer promotion
                return rank(a) >= rank(b) ? a : b;
            }

            static Types getVariableDeclarationType(const std::string &type) {
                if (type == "int8") return Types::Integer8;
                if (type == "int16") return Types::Integer16;
                if (type == "int32") return Types::Integer32;
                if (type == "int") return Types::Integer32;
                if (type == "int64") return Types::Integer64;

                if (type == "uint8") return Types::UnsignedInteger8;
                if (type == "uint16") return Types::UnsignedInteger16;
                if (type == "uint32") return Types::UnsignedInteger32;
                if (type == "uint") return Types::UnsignedInteger32;
                if (type == "uint64") return Types::UnsignedInteger64;

                if (type == "float") return Types::Float;
                if (type == "double") return Types::Double;
                if (type == "bool") return Types::Boolean;
                if (type == "str") return Types::String;

                return Types::None;
            }

            static std::string convertTypeToString(const Types type) {
                if (type == Types::Integer8) return "int8";
                if (type == Types::Integer16) return "int16";
                if (type == Types::Integer32) return "int32";
                if (type == Types::Integer64) return "int64";

                if (type == Types::UnsignedInteger8) return "uint8";
                if (type == Types::UnsignedInteger16) return "uint16";
                if (type == Types::UnsignedInteger32) return "uint32";
                if (type == Types::UnsignedInteger64) return "uint64";

                if (type == Types::Float) return "float";
                if (type == Types::Double) return "double";
                if (type == Types::Boolean) return "boolean";
                if (type == Types::String) return "string";

                return "";
            }


            static bool isImplicitlyAssignable(const Types from, const Types to) {
                if (from == to) return true;

                using T = Types;

                // =========================
                // INTEGER WIDENING ONLY (INT → INT)
                // =========================
                if (from == T::Integer8 && to == T::Integer16) return true;
                if (from == T::Integer16 && to == T::Integer32) return true;
                if (from == T::Integer32 && to == T::Integer64) return true;

                // =========================
                // FLOAT RULE (STRICT)
                // =========================
                // ONLY float literal → float allowed
                if (to == T::Float) {
                    return from == T::Float;
                }

                // DOUBLE RULE (you can decide similarly strict or not)
                if (to == T::Double) {
                    return from == T::Double || from == T::Float;
                }

                // =========================
                // INTEGER → DOUBLE (optional strict rule)
                // =========================
                if (from == T::Integer8 && to == T::Double) return false;
                if (from == T::Integer16 && to == T::Double) return false;
                if (from == T::Integer32 && to == T::Double) return false;
                if (from == T::Integer64 && to == T::Double) return false;

                // =========================
                // FLOAT → INT (never allowed)
                // =========================
                if (from == T::Float || from == T::Double) {
                    if (to == T::Integer8 ||
                        to == T::Integer16 ||
                        to == T::Integer32 ||
                        to == T::Integer64) {
                        return false;
                    }
                }

                return false;
            }
    };
}