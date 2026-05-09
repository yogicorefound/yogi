
// Generated from Grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "Grammar.h"


/**
 * This interface defines an abstract listener for a parse tree produced by Grammar.
 */
class  GrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(Grammar::ProgramContext *ctx) = 0;
  virtual void exitProgram(Grammar::ProgramContext *ctx) = 0;

  virtual void enterStatements(Grammar::StatementsContext *ctx) = 0;
  virtual void exitStatements(Grammar::StatementsContext *ctx) = 0;

  virtual void enterDictionaryDeclaration(Grammar::DictionaryDeclarationContext *ctx) = 0;
  virtual void exitDictionaryDeclaration(Grammar::DictionaryDeclarationContext *ctx) = 0;

  virtual void enterDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext *ctx) = 0;
  virtual void exitDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext *ctx) = 0;

  virtual void enterDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext *ctx) = 0;
  virtual void exitDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext *ctx) = 0;

  virtual void enterDictionaryTypeElement(Grammar::DictionaryTypeElementContext *ctx) = 0;
  virtual void exitDictionaryTypeElement(Grammar::DictionaryTypeElementContext *ctx) = 0;

  virtual void enterDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext *ctx) = 0;
  virtual void exitDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext *ctx) = 0;

  virtual void enterDictionaryDataType(Grammar::DictionaryDataTypeContext *ctx) = 0;
  virtual void exitDictionaryDataType(Grammar::DictionaryDataTypeContext *ctx) = 0;

  virtual void enterExpression(Grammar::ExpressionContext *ctx) = 0;
  virtual void exitExpression(Grammar::ExpressionContext *ctx) = 0;

  virtual void enterConditionalExpression(Grammar::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(Grammar::ConditionalExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(Grammar::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(Grammar::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(Grammar::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(Grammar::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterBitwiseOrExpression(Grammar::BitwiseOrExpressionContext *ctx) = 0;
  virtual void exitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext *ctx) = 0;

  virtual void enterBitwiseXorExpression(Grammar::BitwiseXorExpressionContext *ctx) = 0;
  virtual void exitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext *ctx) = 0;

  virtual void enterBitwiseAndExpression(Grammar::BitwiseAndExpressionContext *ctx) = 0;
  virtual void exitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(Grammar::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(Grammar::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(Grammar::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(Grammar::RelationalExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(Grammar::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(Grammar::ShiftExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(Grammar::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(Grammar::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(Grammar::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterPowerExpression(Grammar::PowerExpressionContext *ctx) = 0;
  virtual void exitPowerExpression(Grammar::PowerExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(Grammar::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(Grammar::UnaryExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(Grammar::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(Grammar::PrimaryExpressionContext *ctx) = 0;

  virtual void enterLiterals(Grammar::LiteralsContext *ctx) = 0;
  virtual void exitLiterals(Grammar::LiteralsContext *ctx) = 0;

  virtual void enterNumberLiterals(Grammar::NumberLiteralsContext *ctx) = 0;
  virtual void exitNumberLiterals(Grammar::NumberLiteralsContext *ctx) = 0;

  virtual void enterStringLiterals(Grammar::StringLiteralsContext *ctx) = 0;
  virtual void exitStringLiterals(Grammar::StringLiteralsContext *ctx) = 0;

  virtual void enterFormattedString(Grammar::FormattedStringContext *ctx) = 0;
  virtual void exitFormattedString(Grammar::FormattedStringContext *ctx) = 0;

  virtual void enterFormattedStringContent(Grammar::FormattedStringContentContext *ctx) = 0;
  virtual void exitFormattedStringContent(Grammar::FormattedStringContentContext *ctx) = 0;

  virtual void enterStringLiteral(Grammar::StringLiteralContext *ctx) = 0;
  virtual void exitStringLiteral(Grammar::StringLiteralContext *ctx) = 0;

  virtual void enterFloatLiteral(Grammar::FloatLiteralContext *ctx) = 0;
  virtual void exitFloatLiteral(Grammar::FloatLiteralContext *ctx) = 0;

  virtual void enterIntegerLiteral(Grammar::IntegerLiteralContext *ctx) = 0;
  virtual void exitIntegerLiteral(Grammar::IntegerLiteralContext *ctx) = 0;

  virtual void enterBooleanLiteral(Grammar::BooleanLiteralContext *ctx) = 0;
  virtual void exitBooleanLiteral(Grammar::BooleanLiteralContext *ctx) = 0;

  virtual void enterNoneLiteral(Grammar::NoneLiteralContext *ctx) = 0;
  virtual void exitNoneLiteral(Grammar::NoneLiteralContext *ctx) = 0;

  virtual void enterIdentifierLiteral(Grammar::IdentifierLiteralContext *ctx) = 0;
  virtual void exitIdentifierLiteral(Grammar::IdentifierLiteralContext *ctx) = 0;

  virtual void enterMemberExpression(Grammar::MemberExpressionContext *ctx) = 0;
  virtual void exitMemberExpression(Grammar::MemberExpressionContext *ctx) = 0;

  virtual void enterValuePostfix(Grammar::ValuePostfixContext *ctx) = 0;
  virtual void exitValuePostfix(Grammar::ValuePostfixContext *ctx) = 0;

  virtual void enterArgumentList(Grammar::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(Grammar::ArgumentListContext *ctx) = 0;

  virtual void enterValueAtom(Grammar::ValueAtomContext *ctx) = 0;
  virtual void exitValueAtom(Grammar::ValueAtomContext *ctx) = 0;

  virtual void enterVariables(Grammar::VariablesContext *ctx) = 0;
  virtual void exitVariables(Grammar::VariablesContext *ctx) = 0;

  virtual void enterVariableDeclaration(Grammar::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(Grammar::VariableDeclarationContext *ctx) = 0;

  virtual void enterVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext *ctx) = 0;
  virtual void exitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext *ctx) = 0;

  virtual void enterVariableReAssignment(Grammar::VariableReAssignmentContext *ctx) = 0;
  virtual void exitVariableReAssignment(Grammar::VariableReAssignmentContext *ctx) = 0;

  virtual void enterVariableDataType(Grammar::VariableDataTypeContext *ctx) = 0;
  virtual void exitVariableDataType(Grammar::VariableDataTypeContext *ctx) = 0;

  virtual void enterArrays(Grammar::ArraysContext *ctx) = 0;
  virtual void exitArrays(Grammar::ArraysContext *ctx) = 0;

  virtual void enterArrayAccess(Grammar::ArrayAccessContext *ctx) = 0;
  virtual void exitArrayAccess(Grammar::ArrayAccessContext *ctx) = 0;

  virtual void enterArrayIndexList(Grammar::ArrayIndexListContext *ctx) = 0;
  virtual void exitArrayIndexList(Grammar::ArrayIndexListContext *ctx) = 0;

  virtual void enterArrayDeclaration(Grammar::ArrayDeclarationContext *ctx) = 0;
  virtual void exitArrayDeclaration(Grammar::ArrayDeclarationContext *ctx) = 0;

  virtual void enterArrayValues(Grammar::ArrayValuesContext *ctx) = 0;
  virtual void exitArrayValues(Grammar::ArrayValuesContext *ctx) = 0;

  virtual void enterArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext *ctx) = 0;
  virtual void exitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext *ctx) = 0;

  virtual void enterArrayItem(Grammar::ArrayItemContext *ctx) = 0;
  virtual void exitArrayItem(Grammar::ArrayItemContext *ctx) = 0;

  virtual void enterArrayElement(Grammar::ArrayElementContext *ctx) = 0;
  virtual void exitArrayElement(Grammar::ArrayElementContext *ctx) = 0;

  virtual void enterArrayReAssignment(Grammar::ArrayReAssignmentContext *ctx) = 0;
  virtual void exitArrayReAssignment(Grammar::ArrayReAssignmentContext *ctx) = 0;

  virtual void enterArrayType(Grammar::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(Grammar::ArrayTypeContext *ctx) = 0;

  virtual void enterArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext *ctx) = 0;
  virtual void exitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext *ctx) = 0;

  virtual void enterArrayDataType(Grammar::ArrayDataTypeContext *ctx) = 0;
  virtual void exitArrayDataType(Grammar::ArrayDataTypeContext *ctx) = 0;

  virtual void enterIfStatement(Grammar::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(Grammar::IfStatementContext *ctx) = 0;

  virtual void enterElseIfStatement(Grammar::ElseIfStatementContext *ctx) = 0;
  virtual void exitElseIfStatement(Grammar::ElseIfStatementContext *ctx) = 0;

  virtual void enterIfStatementCondition(Grammar::IfStatementConditionContext *ctx) = 0;
  virtual void exitIfStatementCondition(Grammar::IfStatementConditionContext *ctx) = 0;

  virtual void enterElseStatement(Grammar::ElseStatementContext *ctx) = 0;
  virtual void exitElseStatement(Grammar::ElseStatementContext *ctx) = 0;

  virtual void enterIfStatementBody(Grammar::IfStatementBodyContext *ctx) = 0;
  virtual void exitIfStatementBody(Grammar::IfStatementBodyContext *ctx) = 0;

  virtual void enterImportStatement(Grammar::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(Grammar::ImportStatementContext *ctx) = 0;

  virtual void enterImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext *ctx) = 0;
  virtual void exitImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext *ctx) = 0;

  virtual void enterImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext *ctx) = 0;
  virtual void exitImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext *ctx) = 0;


};

