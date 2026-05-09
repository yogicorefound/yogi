parser grammar ImportGrammar;

import LiteralsGrammar;



importStatement
    : importStatementWithBrackets
    | importStatementWithoutBrackets
    ;


// import {var1, var2, method1, method2} from "utils.io"
importStatementWithBrackets
    : IMPORT LBRACKET (identifierLiteral (COMMA identifierLiteral)*)? RBRACKET FROM stringLiteral
    ;


// import utils from "utils.io"
importStatementWithoutBrackets
    : IMPORT identifierLiteral FROM stringLiteral
    ;




