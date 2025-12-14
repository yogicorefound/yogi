// StringTokens.g4
lexer grammar StringTokens;

// =======================================================================================================================================================
// StringTokens
// =======================================================================================================================================================



STRING
    : '"' (ESC_SEQ | ~["\\\r\n])* '"'
    | '\'' (ESC_SEQ | ~["\\\r\n])* '\''
    ;

// F-STRING START
FORMATTED_STRING_START
    : 'f"' -> pushMode(FSTRING_MODE)
    ;

// FSTRING_MODE
mode FSTRING_MODE;


// any text until { or end quote
FORMATTED_STRING_TEXT
    : ( ESC_SEQ | ~["\\{}] )+
    ;

// enter expression mode
LBRACE_IN_FSTRING
    : '{' -> pushMode(EXPR_MODE)
    ;

// end of f-string
FORMATTED_STRING_END
    : '"' -> popMode
    ;

// EXPR_MODE — expression inside f-string
mode EXPR_MODE;

RBRACE_IN_FSTRING : '}' -> popMode;

// Operators FIRST
PLUS_IN_EXPR    : '+' -> type(PLUS);
MINUS_IN_EXPR   : '-' -> type(MINUS);
MUL_IN_EXPR     : '*' -> type(MUL);
DIV_IN_EXPR     : '/' -> type(DIV);

LPAREN_IN_EXPR  : '(' -> type(LPAREN);
RPAREN_IN_EXPR  : ')' -> type(RPAREN);

// Literals
NONE_IN_EXPR        : 'none' -> type(NONE);
BOOLEAN_IN_EXPR     : ('true' | 'false') -> type(BOOLEAN);

FLOAT_IN_EXPR       : (DIGIT+ '.' DIGIT* EXPONENT? | '.' DIGIT+ EXPONENT?) -> type(FLOAT);
INTEGER_IN_EXPR     : DIGIT+ -> type(INTEGER);

// Identifiers
ID_IN_EXPR          : [a-zA-Z_] [a-zA-Z_0-9]* -> type(IDENTIFIER);

// Strings
STRING_IN_EXPR      : '"' (ESC_SEQ | ~["\\\r\n])* '"' -> type(STRING);

EXPR_WS : [ \t\r\n]+ -> skip;

