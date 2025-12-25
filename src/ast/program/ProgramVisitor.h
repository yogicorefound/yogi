//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "ast/arrays/ArraysVisitor.h"
#include "ast/base/BaseVisitor.h"
#include "ast/dictionaries/DictionaryVisitor.h"
#include "ast/expressions/ExpressionVisitor.h"
#include "ast/literals/LiteralsVisitor.h"
#include "ast/members/MembersVisitor.h"
#include "ast/variables/VariablesVisitor.h"

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

