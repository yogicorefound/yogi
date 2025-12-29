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
    : literals
    | LPAREN binaryExpression RPAREN
    | binaryExpression expressionOperator binaryExpression
    ;


expressionOperator: (MUL | DIV | MOD | PLUS | MINUS);