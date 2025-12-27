parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar, MembersGrammar;

expression
          : booleanLiteral
          | numberLiterals
          | binaryExpression
          | concatenationExpression
          | identifierLiteral
          | memberExpression
          ;


concatenationExpression
    :  ((stringLiterals | identifierLiteral) (PLUS (stringLiterals | identifierLiteral))*)+
    ;




binaryExpression
    : numberLiterals
    | identifierLiteral
    | LPAREN binaryExpression RPAREN
    | binaryExpression (MUL | DIV | MOD) binaryExpression
    | binaryExpression (PLUS | MINUS) binaryExpression
    ;