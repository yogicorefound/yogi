parser grammar ExportGrammar;

import LiteralsGrammar, VariableGrammar;

options {
    tokenVocab = Tokens;
}

exportStatement
    : exportDeclaration
    | reExportAll
    | reExportWithBrackets
    ;

// export int a = 10
exportDeclaration
    : EXPORT variableDeclaration
    ;

// export { var1, var2 } from "utils.io"
reExportWithBrackets
    : EXPORT LBRACE identifierLiteral (COMMA identifierLiteral)* RBRACE FROM stringLiteral
    ;


// export * from "utils.io"
reExportAll
    : EXPORT MUL FROM stringLiteral
    ;