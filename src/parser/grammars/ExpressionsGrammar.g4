parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar, MembersGrammar;

expression
          : booleanLiteral
          | numberLiterals
          | identifierLiteral
          | concatenationExpression
          | binaryExpression
          | memberExpression
          ;


concatenationExpression
    :  (stringLiterals (PLUS stringLiterals)*)+
    ;


binaryExpression
    : numberLiterals
    | identifierLiteral
    | LPAREN binaryExpression RPAREN
    | binaryExpression (MUL | DIV | MOD) binaryExpression
    | binaryExpression (PLUS | MINUS) binaryExpression
    ;