parser grammar ArraysGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar;
arrays
    : arrayDeclaration
    | arrayReAssignment
    ;

arrayDeclaration
    : arrayType IDENTIFIER EQ arrayValues
    ;

arrayValues
    : arrayItemsWithBrackets
    | expression*          // Para inicialización plana
    | memberExpression
    ;

arrayItemsWithBrackets
    : LBRACKET (arrayItem (COMMA arrayItem)*)? RBRACKET
    ;

arrayItem
    : arrayItemsWithBrackets   // Permite arrays anidados
    | arrayElement
    ;

arrayElement
    : stringLiteral
    | formattedString
    | identifierLiteral
    | integerLiteral
    | floatLiteral
    | booleanLiteral
    | noneLiteral
    | expression
    ;

arrayReAssignment
    : IDENTIFIER EQ arrayItemsWithBrackets
    ;

// ---------------------
// Array type con dimensión opcional
// ---------------------
arrayType
    : arrayDataType (LBRACKET arrayDeclarationTypeSizes? RBRACKET)?
    ;

arrayDeclarationTypeSizes
    : expression (COMMA expression)*  // ✨ múltiples dimensiones
    ;

arrayDataType
    : INTEGER_TYPES
    | UNSIGNED_INTEGER_TYPES
    | FLOAT_TYPES
    | BOOLEAN_TYPES
    | STRING_TYPES
    ;
