parser grammar ExpressionsGrammar;

options {
    tokenVocab = Tokens;
}

import LiteralsGrammar;

expression: literal
          | LPAREN expression RPAREN
          | expression MOD expression
          | expression PLUS expression
          | expression MINUS expression
          | expression MUL expression
          | expression DIV expression
          ;
