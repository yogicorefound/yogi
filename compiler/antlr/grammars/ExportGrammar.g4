parser grammar ExportGrammar;

import LiteralsGrammar, VariableGrammar;

options {
    tokenVocab = Tokens;
}

exportStatement
    : exportDefaultStatement
    | exportNamedStatement
    | exportNamedGroupStatement
    | exportDeclarationStatement
    ;

// export default a
exportDefaultStatement
    : EXPORT DEFAULT expression
    | EXPORT DEFAULT exportSpecifierWithBraces
    ;

// export a
exportNamedStatement
    : EXPORT exportSpecifier
    ;

// export { a, b as c }
exportNamedGroupStatement
    : EXPORT exportSpecifierWithBraces
    ;

exportSpecifierWithBraces
    : LBRACE exportSpecifier (COMMA exportSpecifier)* COMMA? RBRACE
    ;

exportSpecifier
    : identifierLiteral (AS identifierLiteral)?
    ;

// export int a = 10
exportDeclarationStatement
    : EXPORT variableDeclaration
    ;