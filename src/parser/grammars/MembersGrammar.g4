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

// -------------------------
// Atomic values
// -------------------------
valueAtom
    : identifierLiteral
    | stringLiteral
    | numberLiterals
    | booleanLiteral
    | LPAREN expression RPAREN
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
