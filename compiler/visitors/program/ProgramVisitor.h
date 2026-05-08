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
#include "visitors/variables/VariablesVisitor.h"
#include "utils/helpers/cache/cache.h"

namespace yogi::visitor {
    class Visitor final : public utils::helper::cache::Cache, public LiteralsVisitor, public MembersVisitor, public ArraysVisitor, public VariablesVisitor, public DictionaryVisitor, public ExpressionVisitor, public ConditionsVisitor {
        public:
            explicit Visitor(std::string &source, std::string &filePath, Grammar *parser)
                : BaseVisitor(source, filePath, parser), Cache(getBuildDirectory()), LiteralsVisitor(), MembersVisitor(), ArraysVisitor(), VariablesVisitor(), DictionaryVisitor(), ExpressionVisitor(), ConditionsVisitor(), source(source), filePath(filePath), parser(parser) {
            }

            std::any visitProgram(Grammar::ProgramContext *ctx) override;

            std::any visitStatements(Grammar::StatementsContext *ctx) override;

        private:
            std::string &source;
            std::string &filePath;
            Grammar *parser;
    };
} // namespace yogi::visitor