parser grammar VariableGrammar;

options {
    tokenVocab = Tokens;
}


import ExpressionsGrammar, ArraysGrammar;

variables
    :   variableDeclaration
    |   variableDeclarationWithoutAssignment
    |   variableReAssignment
    ;

variableDeclaration: variableDataType IDENTIFIER EQ {inVarMode= true;} expression {inVarMode = false;};


variableDeclarationWithoutAssignment: variableDataType IDENTIFIER;

variableReAssignment: IDENTIFIER EQ expression;
//
//variableAccessToMember
//    : {inSkipMode = true;} IDENTIFIER DOT IDENTIFIER {inSkipMode = false;};

variableDataType: INTEGER_TYPES | UNSIGNED_INTEGER_TYPES | FLOAT_TYPES | BOOLEAN_TYPES | STRING_TYPES;



