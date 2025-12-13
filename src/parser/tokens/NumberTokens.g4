lexer grammar NumberTokens;

// =======================================================================================================================================================
// NumberTokens
// =======================================================================================================================================================

// float
FLOAT
    : [+-]? DIGIT+ '.' DIGIT*
    | [+-]? DIGIT+ '.' DIGIT* EXPONENT?
    | '.' DIGIT+ EXPONENT?
    | [+-]? '0x' DIGIT+ 'p' [+-]? DIGIT+
    ;

FLOAT_UNDERSCORE_EXPONENT
    : DIGIT+ (UNDERSCORE? DIGIT)* '.' DIGIT* (UNDERSCORE? DIGIT)* EXPONENT? -> type(FLOAT)
    ;

FLOAT_HEX
    : [+-]? '0x' DIGIT+ '.' DIGIT* 'p' [+-]? DIGIT+ -> type(FLOAT)
    ;


INTEGER
    : DIGIT+ // Decimal
    | [+-]? '0x' HEX_DIGIT+ // Hexadecimal
    | [+-]? '0o' OCT_DIGIT+ // Octal
    | [+-]? '0b' BINARY_DIGIT+ // Binary
    | [+-]? DIGIT+  EXPONENT?
    | DIGIT+ (UNDERSCORE? DIGIT)*
    ;
