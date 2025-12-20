parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar;

expression: concatenationExpression
          | binaryExpression
          | numberLiterals
          | memberExpression
          ;


concatenationExpression
    :  (stringLiterals (PLUS stringLiterals)*)+
    ;


binaryExpression
    : numberLiterals
    | LPAREN binaryExpression RPAREN
    | binaryExpression (MUL | DIV | MOD) binaryExpression
    | binaryExpression (PLUS | MINUS) binaryExpression
    ;