parser grammar ImportGrammar;

import LiteralsGrammar;

options {
    tokenVocab = Tokens;
}

importStatement
    : importStatementWithoutBrackets
    | importStatementWithBrackets
    ;

// import { var1, var2 } from "utils.io"
importStatementWithBrackets
    : IMPORT LBRACE identifierLiteral (COMMA identifierLiteral)* RBRACE FROM stringLiteral
    ;

// import utils from "utils.io"
importStatementWithoutBrackets
    : IMPORT identifierLiteral FROM stringLiteral
    ;