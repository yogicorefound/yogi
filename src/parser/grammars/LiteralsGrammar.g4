parser grammar LiteralsGrammar;

options {
    tokenVocab = Tokens;
}

literal: integerLiteral
       | floatLiteral
       | formattedString
       | stringLiteral
       | booleanLiteral
       | identifierLiteral
       ;

formattedString
    : FORMATTED_STRING_START formattedStringContent* FORMATTED_STRING_END
    ;

formattedStringContent
    : FORMATTED_STRING_TEXT
    | LBRACE_IN_FSTRING expression RBRACE_IN_FSTRING
    ;

integerLiteral: INTEGER;
floatLiteral: FLOAT;
stringLiteral: STRING;
booleanLiteral: BOOLEAN;
noneLiteral: NONE;
identifierLiteral: IDENTIFIER;