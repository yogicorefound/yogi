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
    : <assoc=right> binaryExpression MUL MUL binaryExpression
    | binaryExpression (MUL | DIV | MOD) binaryExpression
    | binaryExpression (PLUS | MINUS) binaryExpression
    | (PLUS | MINUS) binaryExpression        // unary
    | LPAREN binaryExpression RPAREN
    | literals
    ;


//
//binaryExpression
//    : literals
//    | LPAREN binaryExpression RPAREN
//    | binaryExpression MUL MUL binaryExpression // to the power
//    | binaryExpression (MUL | DIV | MOD) binaryExpression
//    | binaryExpression (PLUS | MINUS) binaryExpression
//    ;
