//
// Created by Brayhan De Aza on 11/30/25.
//

#ifndef CROMIO_ANTLR_ERROR_LISTENER_H
#define CROMIO_ANTLR_ERROR_LISTENER_H

#include <string>
#include "antlr4-runtime.h"

namespace cromio::utils::errors {
    class AntlrErrorListener final : public antlr4::BaseErrorListener {
       public:
        explicit AntlrErrorListener(const std::string& source);
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPos, const std::string& msg, std::exception_ptr) override;

       private:
        std::vector<std::string> lines;
    };

} // namespace cromio::utils

#endif // CROMIO_ANTLR_ERROR_LISTENER_H
