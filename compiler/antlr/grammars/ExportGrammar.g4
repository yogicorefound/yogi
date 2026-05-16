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
    ;

// export a
exportNamedStatement
    : EXPORT exportSpecifier
    ;

// export { a, b as c }
exportNamedGroupStatement
    : EXPORT LBRACE exportSpecifier (COMMA exportSpecifier)* RBRACE
    ;

exportSpecifier
    : identifierLiteral (AS identifierLiteral)?
    ;

// export int a = 10
exportDeclarationStatement
    : EXPORT variableDeclaration
    ;