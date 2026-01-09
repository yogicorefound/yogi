parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar, MembersGrammar;


expression
    : additiveExpression
    ;

// Additive operators: + and - (numeric addition; + also used for string concatenation)
additiveExpression
    : multiplicativeExpression ((PLUS | MINUS) multiplicativeExpression)*
    ;

// Multiplicative operators: *, /, %
multiplicativeExpression
    : powerExpression ((MUL | DIV | MOD) powerExpression)*
    ;

// Power operator: ** (right-associative)
powerExpression
    : unaryExpression (MUL MUL powerExpression)?
    ;

// Unary operators: +, -
unaryExpression
    : (PLUS | MINUS)? primaryExpression
    ;

// Primary expressions: literals, identifiers, member access, parentheses
primaryExpression
    : literals
    | memberExpression
    | LPAREN expression RPAREN
    ;