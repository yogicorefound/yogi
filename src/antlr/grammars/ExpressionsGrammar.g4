parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar, MembersGrammar;

// --------------------
// Top-level expression
// --------------------
expression
    : conditionalExpression
    ;

// --------------------
// Conditional ternary: ?:
// --------------------
conditionalExpression
    : logicalOrExpression (QUESTION expression COLON expression)?
    ;

// --------------------
// Logical OR: ||
// --------------------
logicalOrExpression
    : logicalAndExpression (OROR logicalAndExpression)*
    ;

// --------------------
// Logical AND: &&
// --------------------
logicalAndExpression
    : bitwiseOrExpression (ANDAND bitwiseOrExpression)*
    ;

// --------------------
// Bitwise OR |
// --------------------
bitwiseOrExpression
    : bitwiseXorExpression (BIT_OR bitwiseXorExpression)*
    ;

// --------------------
// Bitwise XOR ^
// --------------------
bitwiseXorExpression
    : bitwiseAndExpression (BIT_XOR bitwiseAndExpression)*
    ;

// --------------------
// Bitwise AND &
// --------------------
bitwiseAndExpression
    : equalityExpression (AMPERSAND equalityExpression)*
    ;

// --------------------
// Equality: ==, !=
// --------------------
equalityExpression
    : relationalExpression ((EQEQ | NEQ) relationalExpression)*
    ;

// --------------------
// Relational: >, <, >=, <=
// --------------------
// permite comparaciones encadenadas: a < b < c
relationalExpression
    : shiftExpression ((GT | LT | GTE | LTE) shiftExpression)*
    ;

// --------------------
// Shift: <<, >>
// --------------------
shiftExpression
    : additiveExpression ((SHL | SHR) additiveExpression)*
    ;

// --------------------
// Additive: +, -
// --------------------
additiveExpression
    : multiplicativeExpression ((PLUS | MINUS) multiplicativeExpression)*
    ;

// --------------------
// Multiplicative: *, /, %
// --------------------
multiplicativeExpression
    : powerExpression ((MUL | DIV | MOD) powerExpression)*
    ;

// --------------------
// Power: ** (right-associative)
// --------------------
powerExpression
    : unaryExpression (MUL MUL powerExpression)?
    ;

// --------------------
// Unary: !, ~, +, -
// --------------------
unaryExpression
    : (NOT (NOT)* | BIT_NOT | PLUS | MINUS)? primaryExpression
    ;

// --------------------
// Primary
// --------------------
primaryExpression
    : LPAREN expression RPAREN
    | literals
    | memberExpression
    ;
