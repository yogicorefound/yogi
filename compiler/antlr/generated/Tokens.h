
// Generated from Tokens.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  Tokens : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, FROM = 2, REGEX_TYPE = 3, DICT_KEYWORD = 4, BOOLEAN_TYPES = 5, 
    STRING_TYPES = 6, INTEGER_TYPES = 7, UNSIGNED_INTEGER_TYPES = 8, FLOAT_TYPES = 9, 
    IF = 10, ELSE = 11, NONE = 12, BOOLEAN = 13, IDENTIFIER = 14, PLUS = 15, 
    MINUS = 16, MUL = 17, DIV = 18, MOD = 19, EQ = 20, EQEQ = 21, NOT = 22, 
    LPAREN = 23, RPAREN = 24, LBRACE = 25, RBRACE = 26, LBRACKET = 27, RBRACKET = 28, 
    DOT = 29, COMMA = 30, AMPERSAND = 31, ANDAND = 32, OROR = 33, LT = 34, 
    LTE = 35, GT = 36, GTE = 37, NEQ = 38, COLON = 39, QUESTION = 40, BIT_OR = 41, 
    BIT_XOR = 42, BIT_NOT = 43, SHL = 44, SHR = 45, NEWLINE = 46, NEWLINE_VISIBLE = 47, 
    WS_VISIBLE = 48, COMMENT = 49, BLOCK_COMMENT = 50, WS = 51, FLOAT = 52, 
    INTEGER = 53, STRING = 54, FORMATTED_STRING_START = 55, FORMATTED_STRING_TEXT = 56, 
    REGEX_LITERAL = 57, LBRACE_IN_FSTRING = 58, FORMATTED_STRING_END = 59, 
    RBRACE_IN_FSTRING = 60, EXPR_WS = 61
  };

  enum {
    FSTRING_MODE = 1, EXPR_MODE = 2
  };

  explicit Tokens(antlr4::CharStream *input);

  ~Tokens() override;


      bool* inSkipMode = nullptr;
      void setParserFlag(bool* flag) { inSkipMode = flag; }


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.
  void NEWLINEAction(antlr4::RuleContext *context, size_t actionIndex);
  void WS_VISIBLEAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.

};

