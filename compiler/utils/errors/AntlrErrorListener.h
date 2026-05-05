//
// Created by Brayhan De Aza on 11/30/25.
//

#pragma once

#include <string>
#include "antlr4-runtime.h"

namespace yogi::utils::errors {
    class AntlrErrorListener final : public antlr4::BaseErrorListener {
       public:
        explicit AntlrErrorListener(const std::string& source);
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPos, const std::string& msg, std::exception_ptr) override;

       private:
        std::vector<std::string> lines;
    };

} // namespace yogi::utils

