//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include <visitors/conditions/ConditionsVisitor.h>
#include "visitors/arrays/ArraysVisitor.h"
#include "visitors/base/BaseVisitor.h"
#include "visitors/dictionaries/DictionaryVisitor.h"
#include "visitors/expressions/ExpressionVisitor.h"
#include "visitors/literals/LiteralsVisitor.h"
#include "visitors/members/MembersVisitor.h"
#include "visitors/modules/ModulesVisitor.h"
#include "visitors/variables/VariablesVisitor.h"

namespace yogi::visitor {
    class Visitor final : public LiteralsVisitor, public MembersVisitor, public ArraysVisitor, public VariablesVisitor, public DictionaryVisitor, public ExpressionVisitor, public ConditionsVisitor, public ModulesVisitor {
        public:
            explicit Visitor(std::string &source, std::string &filePath, Grammar *parser, const bool justScan)
                : BaseVisitor(source, filePath, filePath, parser), LiteralsVisitor(), MembersVisitor(), ArraysVisitor(), VariablesVisitor(), DictionaryVisitor(), ExpressionVisitor(), ConditionsVisitor(), ModulesVisitor(), entryPath(filePath), justScan(justScan), source(source), filePath(filePath), parser(parser) {
            }

            std::any visitProgram(Grammar::ProgramContext *ctx) override;

            std::any visitStatements(Grammar::StatementsContext *ctx) override;

            std::string &entryPath;

        private:
            bool justScan;
            std::string &source;
            std::string &filePath;
            Grammar *parser;
            nodes::FullProgramASTSNode allASTs; // empty;

    };
} // namespace yogi::visitor