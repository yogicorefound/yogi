
// Generated from Grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "GrammarVisitor.h"


/**
 * This class provides an empty implementation of GrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GrammarBaseVisitor : public GrammarVisitor {
public:

  virtual std::any visitProgram(Grammar::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatements(Grammar::StatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionaryDeclaration(Grammar::DictionaryDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionaryTypeElement(Grammar::DictionaryTypeElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionaryDataType(Grammar::DictionaryDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(Grammar::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalExpression(Grammar::ConditionalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(Grammar::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(Grammar::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(Grammar::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(Grammar::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftExpression(Grammar::ShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(Grammar::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPowerExpression(Grammar::PowerExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(Grammar::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(Grammar::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiterals(Grammar::LiteralsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberLiterals(Grammar::NumberLiteralsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiterals(Grammar::StringLiteralsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormattedString(Grammar::FormattedStringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormattedStringContent(Grammar::FormattedStringContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteral(Grammar::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatLiteral(Grammar::FloatLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntegerLiteral(Grammar::IntegerLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleanLiteral(Grammar::BooleanLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoneLiteral(Grammar::NoneLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierLiteral(Grammar::IdentifierLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberExpression(Grammar::MemberExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValuePostfix(Grammar::ValuePostfixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(Grammar::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValueAtom(Grammar::ValueAtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariables(Grammar::VariablesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(Grammar::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableReAssignment(Grammar::VariableReAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDataType(Grammar::VariableDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrays(Grammar::ArraysContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAccess(Grammar::ArrayAccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayIndexList(Grammar::ArrayIndexListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDeclaration(Grammar::ArrayDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayValues(Grammar::ArrayValuesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayItem(Grammar::ArrayItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayElement(Grammar::ArrayElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayReAssignment(Grammar::ArrayReAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(Grammar::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDataType(Grammar::ArrayDataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(Grammar::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseIfStatement(Grammar::ElseIfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatementCondition(Grammar::IfStatementConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseStatement(Grammar::ElseStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatementBody(Grammar::IfStatementBodyContext *ctx) override {
    return visitChildren(ctx);
  }


};

