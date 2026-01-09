parser grammar LiteralsGrammar;

options {
    tokenVocab = Tokens;
}

literals
    : numberLiterals
    | stringLiterals
    | booleanLiteral
    | identifierLiteral
    ;


numberLiterals
    : integerLiteral
    | floatLiteral
    ;

stringLiterals
    : stringLiteral
    | formattedString
    | identifierLiteral
    ;

formattedString
    : FORMATTED_STRING_START formattedStringContent* FORMATTED_STRING_END
    ;

formattedStringContent
    : REGEX_LITERAL
    | FORMATTED_STRING_TEXT
    | LBRACE_IN_FSTRING expression RBRACE_IN_FSTRING
    ;

stringLiteral
    : STRING
    ;

//regexLiteral: REGEX_START REGEX_CONTENT REGEX_END;

floatLiteral: FLOAT;
integerLiteral: INTEGER;
booleanLiteral: NOT? BOOLEAN;
noneLiteral: NONE;
identifierLiteral: NOT? IDENTIFIER;