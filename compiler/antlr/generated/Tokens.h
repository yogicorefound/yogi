
// Generated from Tokens.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  Tokens : public antlr4::Lexer {
public:
  enum {
    REGEX_TYPE = 1, DICT_KEYWORD = 2, BOOLEAN_TYPES = 3, STRING_TYPES = 4, 
    INTEGER_TYPES = 5, UNSIGNED_INTEGER_TYPES = 6, FLOAT_TYPES = 7, IF = 8, 
    ELSE = 9, NONE = 10, BOOLEAN = 11, IDENTIFIER = 12, PLUS = 13, MINUS = 14, 
    MUL = 15, DIV = 16, MOD = 17, EQ = 18, EQEQ = 19, NOT = 20, LPAREN = 21, 
    RPAREN = 22, LBRACE = 23, RBRACE = 24, LBRACKET = 25, RBRACKET = 26, 
    DOT = 27, COMMA = 28, AMPERSAND = 29, ANDAND = 30, OROR = 31, LT = 32, 
    LTE = 33, GT = 34, GTE = 35, NEQ = 36, COLON = 37, QUESTION = 38, BIT_OR = 39, 
    BIT_XOR = 40, BIT_NOT = 41, SHL = 42, SHR = 43, NEWLINE = 44, NEWLINE_VISIBLE = 45, 
    WS_VISIBLE = 46, COMMENT = 47, BLOCK_COMMENT = 48, WS = 49, FLOAT = 50, 
    INTEGER = 51, STRING = 52, FORMATTED_STRING_START = 53, IMPORT = 54, 
    FROM = 55, FORMATTED_STRING_TEXT = 56, REGEX_LITERAL = 57, LBRACE_IN_FSTRING = 58, 
    FORMATTED_STRING_END = 59, RBRACE_IN_FSTRING = 60, EXPR_WS = 61
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

