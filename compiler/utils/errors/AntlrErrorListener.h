//
// Created by Brayhan De Aza on 11/30/25.
//

#pragma once

#include <string>
#include "antlr4-runtime.h"

namespace yogi::utils::errors {
    class AntlrErrorListener final : public antlr4::BaseErrorListener {
        public:
            explicit AntlrErrorListener(const std::string &source);

            void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPos, const std::string &msg, std::exception_ptr) override;

            bool hasError = false;

        private:
            std::vector<std::string> lines;
    };


    // SafeErrorStrategy.h
    class SafeErrorStrategy : public antlr4::BailErrorStrategy {
        public:
            void recover(antlr4::Parser *recognizer, std::exception_ptr e) override {
                // Walk up context chain and mark as error
                antlr4::ParserRuleContext *context = recognizer->getContext();
                while (context != nullptr) {
                    context->exception = e;
                    context = dynamic_cast<antlr4::ParserRuleContext *>(context->parent);
                }
                // rethrow cleanly
                std::rethrow_exception(e);
            }

            antlr4::Token *recoverInline(antlr4::Parser *recognizer) override {
                antlr4::InputMismatchException e(recognizer);
                antlr4::ParserRuleContext *context = recognizer->getContext();
                while (context != nullptr) {
                    context->exception = std::make_exception_ptr(e);
                    context = dynamic_cast<antlr4::ParserRuleContext *>(context->parent);
                }
                throw e;
            }
    };

} // namespace yogi::utils