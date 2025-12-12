parser grammar DictionaryGrammar;

options {
    tokenVocab = Tokens;
}

import ExpressionsGrammar;

dictionaryDeclaration: DICT_KEYWORD LESSTHAN dictionaryDeclarationType GREATERTHAN IDENTIFIER EQ LBRACE (dictionaryAssignmentBody (COMMA dictionaryAssignmentBody COMMA? )*)? RBRACE;

dictionaryAssignmentBody
    : literal COLON expression
    ;

dictionaryDeclarationType
    : dictionaryTypeElement COMMA dictionaryTypeElement
    ;

dictionaryTypeElement
    : dictionaryDeclarationTypeArray
    | dictionaryDataType
    ;

dictionaryDeclarationTypeArray
    : dictionaryDataType LBRACKET (expression)? RBRACKET
    ;

dictionaryDataType: INTEGER_TYPES | UNSIGNED_INTEGER_TYPES | FLOAT_TYPES | BOOLEAN_TYPES | STRING_TYPES;


