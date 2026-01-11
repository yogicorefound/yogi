parser grammar ConditionsGrammar;

import ExpressionsGrammar, ArraysGrammar, Grammar;

options {
    tokenVocab = Tokens;
}



ifStatement
    : IF LPAREN ifStatementCondition RPAREN ifStatementBody (elseIfStatement* elseStatement?)
    ;


elseIfStatement
    : ELSE IF LPAREN ifStatementCondition? RPAREN ifStatementBody
    ;

ifStatementCondition
    :  expression
    ;

elseStatement
    : ELSE ifStatementBody
    ;

// The body of the if/else: either a block or a single statement
ifStatementBody
    : LBRACE statements* RBRACE
    ;





