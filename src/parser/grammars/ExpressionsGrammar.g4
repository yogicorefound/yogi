parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar;

expression: concatenationExpression
          | binaryExpression
          | stringLiterals
          | numberLiterals
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


// 0311-000-89
// 579-946-7392