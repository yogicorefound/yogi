parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar, MembersGrammar;

// --------------------
// Top-level expression
// --------------------
expression
    : relationalExpression
    ;

// --------------------
// Relational: >, <, >=, <=, ==, !=
// --------------------
relationalExpression
    : additiveExpression ((GT | LT | GTE | LTE | EQEQ | NEQ) additiveExpression)*
    ;

// --------------------
// Additive: +, - (numeric addition, + also string concatenation)
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
// Unary: !, +, -
// --------------------
unaryExpression
    : (NOT (NOT)* | PLUS | MINUS)? primaryExpression
    ;

// --------------------
// Primary: literals, identifiers, members, parentheses
// --------------------
primaryExpression
    : LPAREN expression RPAREN           // parentheses allow nested full expressions
    | literals
    | memberExpression
    ;
