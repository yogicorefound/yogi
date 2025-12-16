parser grammar Grammar;

options {
    tokenVocab = Tokens;
}

@parser::members {
    public:
        bool inVarMode = false;
        bool inSkipMode = false;
}

import DictionaryGrammar, VariableGrammar, ArraysGrammar, MembersGrammar,  LiteralsGrammar, ExpressionsGrammar;

program: NEWLINE* (statements NEWLINE*)* EOF;

statements
    : variables
    | arrays
    | dictionaryDeclaration
    | memberExpression
    | expression
    ;

