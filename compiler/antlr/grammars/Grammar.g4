parser grammar Grammar;

options {
    tokenVocab = Tokens;
}

@parser::members {
    public:
        bool inVarMode = false;
        bool inSkipMode = false;
        bool isNotOperator = false;
}

import ImportGrammar, ExportGrammar, DictionaryGrammar, VariableGrammar, ConditionsGrammar, ArraysGrammar, MembersGrammar,  LiteralsGrammar, ExpressionsGrammar;

program: NEWLINE* (statements NEWLINE*)* EOF;

statements
    : expression
    | variables
    | arrays
    | importStatement
    | exportStatement
    | dictionaryDeclaration
    | memberExpression
    | ifStatement
    | booleanLiteral
    | noneLiteral
    ;

