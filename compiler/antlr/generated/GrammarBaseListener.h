
// Generated from Grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "GrammarListener.h"


/**
 * This class provides an empty implementation of GrammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  GrammarBaseListener : public GrammarListener {
public:

  virtual void enterProgram(Grammar::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(Grammar::ProgramContext * /*ctx*/) override { }

  virtual void enterStatements(Grammar::StatementsContext * /*ctx*/) override { }
  virtual void exitStatements(Grammar::StatementsContext * /*ctx*/) override { }

  virtual void enterImportStatement(Grammar::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(Grammar::ImportStatementContext * /*ctx*/) override { }

  virtual void enterImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext * /*ctx*/) override { }
  virtual void exitImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext * /*ctx*/) override { }

  virtual void enterImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext * /*ctx*/) override { }
  virtual void exitImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext * /*ctx*/) override { }

  virtual void enterLiterals(Grammar::LiteralsContext * /*ctx*/) override { }
  virtual void exitLiterals(Grammar::LiteralsContext * /*ctx*/) override { }

  virtual void enterNumberLiterals(Grammar::NumberLiteralsContext * /*ctx*/) override { }
  virtual void exitNumberLiterals(Grammar::NumberLiteralsContext * /*ctx*/) override { }

  virtual void enterStringLiterals(Grammar::StringLiteralsContext * /*ctx*/) override { }
  virtual void exitStringLiterals(Grammar::StringLiteralsContext * /*ctx*/) override { }

  virtual void enterFormattedString(Grammar::FormattedStringContext * /*ctx*/) override { }
  virtual void exitFormattedString(Grammar::FormattedStringContext * /*ctx*/) override { }

  virtual void enterFormattedStringContent(Grammar::FormattedStringContentContext * /*ctx*/) override { }
  virtual void exitFormattedStringContent(Grammar::FormattedStringContentContext * /*ctx*/) override { }

  virtual void enterStringLiteral(Grammar::StringLiteralContext * /*ctx*/) override { }
  virtual void exitStringLiteral(Grammar::StringLiteralContext * /*ctx*/) override { }

  virtual void enterFloatLiteral(Grammar::FloatLiteralContext * /*ctx*/) override { }
  virtual void exitFloatLiteral(Grammar::FloatLiteralContext * /*ctx*/) override { }

  virtual void enterIntegerLiteral(Grammar::IntegerLiteralContext * /*ctx*/) override { }
  virtual void exitIntegerLiteral(Grammar::IntegerLiteralContext * /*ctx*/) override { }

  virtual void enterBooleanLiteral(Grammar::BooleanLiteralContext * /*ctx*/) override { }
  virtual void exitBooleanLiteral(Grammar::BooleanLiteralContext * /*ctx*/) override { }

  virtual void enterNoneLiteral(Grammar::NoneLiteralContext * /*ctx*/) override { }
  virtual void exitNoneLiteral(Grammar::NoneLiteralContext * /*ctx*/) override { }

  virtual void enterIdentifierLiteral(Grammar::IdentifierLiteralContext * /*ctx*/) override { }
  virtual void exitIdentifierLiteral(Grammar::IdentifierLiteralContext * /*ctx*/) override { }

  virtual void enterExpression(Grammar::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(Grammar::ExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(Grammar::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(Grammar::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(Grammar::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(Grammar::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(Grammar::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(Grammar::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseOrExpression(Grammar::BitwiseOrExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseXorExpression(Grammar::BitwiseXorExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseAndExpression(Grammar::BitwiseAndExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(Grammar::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(Grammar::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(Grammar::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(Grammar::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterShiftExpression(Grammar::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(Grammar::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(Grammar::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(Grammar::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(Grammar::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterPowerExpression(Grammar::PowerExpressionContext * /*ctx*/) override { }
  virtual void exitPowerExpression(Grammar::PowerExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(Grammar::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(Grammar::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(Grammar::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(Grammar::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterMemberExpression(Grammar::MemberExpressionContext * /*ctx*/) override { }
  virtual void exitMemberExpression(Grammar::MemberExpressionContext * /*ctx*/) override { }

  virtual void enterValuePostfix(Grammar::ValuePostfixContext * /*ctx*/) override { }
  virtual void exitValuePostfix(Grammar::ValuePostfixContext * /*ctx*/) override { }

  virtual void enterArgumentList(Grammar::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(Grammar::ArgumentListContext * /*ctx*/) override { }

  virtual void enterValueAtom(Grammar::ValueAtomContext * /*ctx*/) override { }
  virtual void exitValueAtom(Grammar::ValueAtomContext * /*ctx*/) override { }

  virtual void enterDictionaryDeclaration(Grammar::DictionaryDeclarationContext * /*ctx*/) override { }
  virtual void exitDictionaryDeclaration(Grammar::DictionaryDeclarationContext * /*ctx*/) override { }

  virtual void enterDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext * /*ctx*/) override { }
  virtual void exitDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext * /*ctx*/) override { }

  virtual void enterDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext * /*ctx*/) override { }
  virtual void exitDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext * /*ctx*/) override { }

  virtual void enterDictionaryTypeElement(Grammar::DictionaryTypeElementContext * /*ctx*/) override { }
  virtual void exitDictionaryTypeElement(Grammar::DictionaryTypeElementContext * /*ctx*/) override { }

  virtual void enterDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext * /*ctx*/) override { }
  virtual void exitDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext * /*ctx*/) override { }

  virtual void enterDictionaryDataType(Grammar::DictionaryDataTypeContext * /*ctx*/) override { }
  virtual void exitDictionaryDataType(Grammar::DictionaryDataTypeContext * /*ctx*/) override { }

  virtual void enterVariables(Grammar::VariablesContext * /*ctx*/) override { }
  virtual void exitVariables(Grammar::VariablesContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(Grammar::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(Grammar::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext * /*ctx*/) override { }
  virtual void exitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext * /*ctx*/) override { }

  virtual void enterVariableReAssignment(Grammar::VariableReAssignmentContext * /*ctx*/) override { }
  virtual void exitVariableReAssignment(Grammar::VariableReAssignmentContext * /*ctx*/) override { }

  virtual void enterVariableDataType(Grammar::VariableDataTypeContext * /*ctx*/) override { }
  virtual void exitVariableDataType(Grammar::VariableDataTypeContext * /*ctx*/) override { }

  virtual void enterArrays(Grammar::ArraysContext * /*ctx*/) override { }
  virtual void exitArrays(Grammar::ArraysContext * /*ctx*/) override { }

  virtual void enterArrayAccess(Grammar::ArrayAccessContext * /*ctx*/) override { }
  virtual void exitArrayAccess(Grammar::ArrayAccessContext * /*ctx*/) override { }

  virtual void enterArrayIndexList(Grammar::ArrayIndexListContext * /*ctx*/) override { }
  virtual void exitArrayIndexList(Grammar::ArrayIndexListContext * /*ctx*/) override { }

  virtual void enterArrayDeclaration(Grammar::ArrayDeclarationContext * /*ctx*/) override { }
  virtual void exitArrayDeclaration(Grammar::ArrayDeclarationContext * /*ctx*/) override { }

  virtual void enterArrayValues(Grammar::ArrayValuesContext * /*ctx*/) override { }
  virtual void exitArrayValues(Grammar::ArrayValuesContext * /*ctx*/) override { }

  virtual void enterArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext * /*ctx*/) override { }
  virtual void exitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext * /*ctx*/) override { }

  virtual void enterArrayItem(Grammar::ArrayItemContext * /*ctx*/) override { }
  virtual void exitArrayItem(Grammar::ArrayItemContext * /*ctx*/) override { }

  virtual void enterArrayElement(Grammar::ArrayElementContext * /*ctx*/) override { }
  virtual void exitArrayElement(Grammar::ArrayElementContext * /*ctx*/) override { }

  virtual void enterArrayReAssignment(Grammar::ArrayReAssignmentContext * /*ctx*/) override { }
  virtual void exitArrayReAssignment(Grammar::ArrayReAssignmentContext * /*ctx*/) override { }

  virtual void enterArrayType(Grammar::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(Grammar::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext * /*ctx*/) override { }
  virtual void exitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext * /*ctx*/) override { }

  virtual void enterArrayDataType(Grammar::ArrayDataTypeContext * /*ctx*/) override { }
  virtual void exitArrayDataType(Grammar::ArrayDataTypeContext * /*ctx*/) override { }

  virtual void enterIfStatement(Grammar::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(Grammar::IfStatementContext * /*ctx*/) override { }

  virtual void enterElseIfStatement(Grammar::ElseIfStatementContext * /*ctx*/) override { }
  virtual void exitElseIfStatement(Grammar::ElseIfStatementContext * /*ctx*/) override { }

  virtual void enterIfStatementCondition(Grammar::IfStatementConditionContext * /*ctx*/) override { }
  virtual void exitIfStatementCondition(Grammar::IfStatementConditionContext * /*ctx*/) override { }

  virtual void enterElseStatement(Grammar::ElseStatementContext * /*ctx*/) override { }
  virtual void exitElseStatement(Grammar::ElseStatementContext * /*ctx*/) override { }

  virtual void enterIfStatementBody(Grammar::IfStatementBodyContext * /*ctx*/) override { }
  virtual void exitIfStatementBody(Grammar::IfStatementBodyContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

