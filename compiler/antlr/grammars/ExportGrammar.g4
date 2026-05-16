parser grammar ExportGrammar;

import LiteralsGrammar, VariableGrammar;

options {
    tokenVocab = Tokens;
}


exportStatement
    : exportMultipleIdentifiers
    | exportVariableDeclaration
    | exportIdentifier
    ;


// -------------------------------------------------
// export multiple identifiers
// -------------------------------------------------
// Examples:
// export { a }
// -------------------------------------------------
exportMultipleIdentifiers
    : EXPORT LBRACE identifierLiteral (COMMA identifierLiteral)* COMMA?  RBRACE
    ;

// -------------------------------------------------
// export identifier
// -------------------------------------------------
// Examples:
// export a
exportIdentifier
    : EXPORT identifierLiteral
    ;

// -------------------------------------------------
// export variable declaration
// -------------------------------------------------
// Examples:
// export int a = 10
exportVariableDeclaration
    : EXPORT variableDeclaration
    ;

