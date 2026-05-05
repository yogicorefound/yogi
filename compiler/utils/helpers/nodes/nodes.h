//
// Created by Brayhan De Aza on 5/1/26.
//

#pragma once


#include <any>
#include <string>
#include "utils/types/Types.h"


namespace yogi::utils::helpers {
    class Nodes {
    public:
        struct EvalExpressionResult {
            Types type;
            std::string value;
            bool error;
            std::string message;
        };


        static double applyOperator(double l, double r, std::string op);

        static EvalExpressionResult evaluateExpression(const std::any &node);
    };
}