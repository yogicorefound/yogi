//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "visitors/arrays/ArraysVisitor.h"
#include "visitors/base/BaseVisitor.h"
#include "visitors/dictionaries/DictionaryVisitor.h"
#include "visitors/expressions/ExpressionVisitor.h"
#include "visitors/literals/LiteralsVisitor.h"
#include "visitors/members/MembersVisitor.h"
#include "visitors/variables/VariablesVisitor.h"

namespace yogi::visitor {
    class Visitor final : public LiteralsVisitor, public MembersVisitor, public ArraysVisitor, public VariablesVisitor, public DictionaryVisitor, public ExpressionVisitor {
       public:
        explicit Visitor(std::string& source, Grammar* parser) : BaseVisitor(source, parser), LiteralsVisitor(), MembersVisitor(), ArraysVisitor(), VariablesVisitor(), DictionaryVisitor(), ExpressionVisitor(), source(source), parser(parser) {}

        std::any visitProgram(Grammar::ProgramContext* ctx) override;
        std::any visitStatements(Grammar::StatementsContext* ctx) override;

       private:
        std::string& source;
        Grammar* parser;
    };
} // namespace yogi::visitor

