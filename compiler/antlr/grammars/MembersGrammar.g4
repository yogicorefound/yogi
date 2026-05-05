parser grammar MembersGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar;

// -------------------------
// Postfix chaining
// -------------------------
memberExpression
    : valueAtom valuePostfix*
    ;


valuePostfix
    : DOT identifierLiteral
    | LPAREN argumentList? RPAREN
    ;


// -------------------------
// Arguments
// -------------------------
argumentList
    : expression (COMMA expression)*
    ;



// -------------------------
// Atomic values
// -------------------------
valueAtom
    : identifierLiteral
    | stringLiteral
    | LPAREN booleanLiteral RPAREN
    | LPAREN numberLiterals RPAREN
    | LPAREN expression RPAREN
    ;
