parser grammar LiteralsGrammar;

options {
    tokenVocab = Tokens;
}

literal
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
    | regexLiteral
    | identifierLiteral
    ;

formattedString
    : FORMATTED_STRING_START formattedStringContent* FORMATTED_STRING_END
    ;

formattedStringContent
    : FORMATTED_STRING_TEXT
    | LBRACE_IN_FSTRING expression RBRACE_IN_FSTRING
    ;

stringLiteral
    : STRING
    ;

regexLiteral: REGEX_START REGEX_CONTENT REGEX_END;

integerLiteral: INTEGER;
floatLiteral: FLOAT;
booleanLiteral: BOOLEAN;
noneLiteral: NONE;
identifierLiteral: IDENTIFIER;