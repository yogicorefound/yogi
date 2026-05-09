
// Generated from Grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "Grammar.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by Grammar.
 */
class  GrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Grammar.
   */
    virtual std::any visitProgram(Grammar::ProgramContext *context) = 0;

    virtual std::any visitStatements(Grammar::StatementsContext *context) = 0;

    virtual std::any visitDictionaryDeclaration(Grammar::DictionaryDeclarationContext *context) = 0;

    virtual std::any visitDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext *context) = 0;

    virtual std::any visitDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext *context) = 0;

    virtual std::any visitDictionaryTypeElement(Grammar::DictionaryTypeElementContext *context) = 0;

    virtual std::any visitDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext *context) = 0;

    virtual std::any visitDictionaryDataType(Grammar::DictionaryDataTypeContext *context) = 0;

    virtual std::any visitExpression(Grammar::ExpressionContext *context) = 0;

    virtual std::any visitConditionalExpression(Grammar::ConditionalExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(Grammar::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(Grammar::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext *context) = 0;

    virtual std::any visitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext *context) = 0;

    virtual std::any visitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(Grammar::EqualityExpressionContext *context) = 0;

    virtual std::any visitRelationalExpression(Grammar::RelationalExpressionContext *context) = 0;

    virtual std::any visitShiftExpression(Grammar::ShiftExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(Grammar::AdditiveExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitPowerExpression(Grammar::PowerExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(Grammar::UnaryExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpression(Grammar::PrimaryExpressionContext *context) = 0;

    virtual std::any visitLiterals(Grammar::LiteralsContext *context) = 0;

    virtual std::any visitNumberLiterals(Grammar::NumberLiteralsContext *context) = 0;

    virtual std::any visitStringLiterals(Grammar::StringLiteralsContext *context) = 0;

    virtual std::any visitFormattedString(Grammar::FormattedStringContext *context) = 0;

    virtual std::any visitFormattedStringContent(Grammar::FormattedStringContentContext *context) = 0;

    virtual std::any visitStringLiteral(Grammar::StringLiteralContext *context) = 0;

    virtual std::any visitFloatLiteral(Grammar::FloatLiteralContext *context) = 0;

    virtual std::any visitIntegerLiteral(Grammar::IntegerLiteralContext *context) = 0;

    virtual std::any visitBooleanLiteral(Grammar::BooleanLiteralContext *context) = 0;

    virtual std::any visitNoneLiteral(Grammar::NoneLiteralContext *context) = 0;

    virtual std::any visitIdentifierLiteral(Grammar::IdentifierLiteralContext *context) = 0;

    virtual std::any visitMemberExpression(Grammar::MemberExpressionContext *context) = 0;

    virtual std::any visitValuePostfix(Grammar::ValuePostfixContext *context) = 0;

    virtual std::any visitArgumentList(Grammar::ArgumentListContext *context) = 0;

    virtual std::any visitValueAtom(Grammar::ValueAtomContext *context) = 0;

    virtual std::any visitVariables(Grammar::VariablesContext *context) = 0;

    virtual std::any visitVariableDeclaration(Grammar::VariableDeclarationContext *context) = 0;

    virtual std::any visitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext *context) = 0;

    virtual std::any visitVariableReAssignment(Grammar::VariableReAssignmentContext *context) = 0;

    virtual std::any visitVariableDataType(Grammar::VariableDataTypeContext *context) = 0;

    virtual std::any visitArrays(Grammar::ArraysContext *context) = 0;

    virtual std::any visitArrayAccess(Grammar::ArrayAccessContext *context) = 0;

    virtual std::any visitArrayIndexList(Grammar::ArrayIndexListContext *context) = 0;

    virtual std::any visitArrayDeclaration(Grammar::ArrayDeclarationContext *context) = 0;

    virtual std::any visitArrayValues(Grammar::ArrayValuesContext *context) = 0;

    virtual std::any visitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext *context) = 0;

    virtual std::any visitArrayItem(Grammar::ArrayItemContext *context) = 0;

    virtual std::any visitArrayElement(Grammar::ArrayElementContext *context) = 0;

    virtual std::any visitArrayReAssignment(Grammar::ArrayReAssignmentContext *context) = 0;

    virtual std::any visitArrayType(Grammar::ArrayTypeContext *context) = 0;

    virtual std::any visitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext *context) = 0;

    virtual std::any visitArrayDataType(Grammar::ArrayDataTypeContext *context) = 0;

    virtual std::any visitIfStatement(Grammar::IfStatementContext *context) = 0;

    virtual std::any visitElseIfStatement(Grammar::ElseIfStatementContext *context) = 0;

    virtual std::any visitIfStatementCondition(Grammar::IfStatementConditionContext *context) = 0;

    virtual std::any visitElseStatement(Grammar::ElseStatementContext *context) = 0;

    virtual std::any visitIfStatementBody(Grammar::IfStatementBodyContext *context) = 0;

    virtual std::any visitImportStatement(Grammar::ImportStatementContext *context) = 0;

    virtual std::any visitImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext *context) = 0;

    virtual std::any visitImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext *context) = 0;


};

