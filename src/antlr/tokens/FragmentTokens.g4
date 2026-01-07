lexer grammar Fragment;


// =======================================================================================================================================================
// FragmentTokens
// =======================================================================================================================================================

fragment DIGIT      : [0-9];
fragment HEX_DIGIT  : [0-9a-fA-F];
fragment EXPONENT   : [eE] [+-]? DIGIT+;
fragment OCT_DIGIT  : [0-7];
fragment BINARY_DIGIT : [01];
fragment UNDERSCORE : '_';
fragment EQUAL : '=';

fragment ESC_SEQ
    : '\\' ['"\\/bfnrt]
    | '\\u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;