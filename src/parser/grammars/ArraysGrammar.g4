parser grammar ArraysGrammar;

options {
    tokenVocab = Tokens;
}

import ExpressionsGrammar;

arrayDeclaration: {inSkipMode = true;} arrayType {inSkipMode = false;} IDENTIFIER EQ LBRACKET (expression (COMMA expression)*)? RBRACKET;

arrayType: arrayDataType LBRACKET arrayDeclarationTypeSize RBRACKET;

arrayDeclarationTypeSize: {inSkipMode = false;} expression? {inSkipMode = true;};

arrayDataType: INTEGER_TYPES | UNSIGNED_INTEGER_TYPES | FLOAT_TYPES | BOOLEAN_TYPES | STRING_TYPES;
