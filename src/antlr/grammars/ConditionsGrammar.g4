parser grammar ConditionsGrammar;

import ExpressionsGrammar, ArraysGrammar, Grammar;

options {
    tokenVocab = Tokens;
}



ifStatement
    : IF LPAREN expression RPAREN ifStatementBody (elseIfStatement* elseStatement?)
    ;


elseIfStatement
    : ELSE IF LPAREN expression? RPAREN ifStatementBody
    ;

elseStatement
    : ELSE ifStatementBody
    ;

// The body of the if/else: either a block or a single statement
ifStatementBody
    : LBRACE statements* RBRACE
    ;





