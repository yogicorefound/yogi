parser grammar ArraysGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar;

arrays
    : arrayDeclaration
    | arrayReAssignment
    ;

arrayDeclaration: {inSkipMode = true;} arrayType {inSkipMode = false;} IDENTIFIER EQ arrayValues;

arrayValues: arrayItemsWithBrackets | expression* | memberExpression;

arrayItemsWithBrackets: LBRACKET (expression (COMMA expression)*)? RBRACKET;

arrayItems
    : stringLiteral
    | formattedString
    | identifierLiteral
    | integerLiteral
    | floatLiteral
    | booleanLiteral
    | noneLiteral
    | concatenationExpression
    | binaryExpression
    ;

arrayReAssignment: IDENTIFIER EQ LBRACKET (expression (COMMA expression)*)? RBRACKET;

arrayType: arrayDataType LBRACKET arrayDeclarationTypeSize RBRACKET;

arrayDeclarationTypeSize: {inSkipMode = false;} expression? {inSkipMode = true;};

arrayDataType: INTEGER_TYPES | UNSIGNED_INTEGER_TYPES | FLOAT_TYPES | BOOLEAN_TYPES | STRING_TYPES;
