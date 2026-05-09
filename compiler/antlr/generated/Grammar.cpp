
// Generated from Grammar.g4 by ANTLR 4.13.2


#include "GrammarListener.h"
#include "GrammarVisitor.h"

#include "Grammar.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct GrammarStaticData final {
  GrammarStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GrammarStaticData(const GrammarStaticData&) = delete;
  GrammarStaticData(GrammarStaticData&&) = delete;
  GrammarStaticData& operator=(const GrammarStaticData&) = delete;
  GrammarStaticData& operator=(GrammarStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag grammarParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<GrammarStaticData> grammarParserStaticData = nullptr;

void grammarParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (grammarParserStaticData != nullptr) {
    return;
  }
#else
  assert(grammarParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<GrammarStaticData>(
    std::vector<std::string>{
      "program", "statements", "dictionaryDeclaration", "dictionaryAssignmentBody", 
      "dictionaryDeclarationType", "dictionaryTypeElement", "dictionaryDeclarationTypeArray", 
      "dictionaryDataType", "expression", "conditionalExpression", "logicalOrExpression", 
      "logicalAndExpression", "bitwiseOrExpression", "bitwiseXorExpression", 
      "bitwiseAndExpression", "equalityExpression", "relationalExpression", 
      "shiftExpression", "additiveExpression", "multiplicativeExpression", 
      "powerExpression", "unaryExpression", "primaryExpression", "literals", 
      "numberLiterals", "stringLiterals", "formattedString", "formattedStringContent", 
      "stringLiteral", "floatLiteral", "integerLiteral", "booleanLiteral", 
      "noneLiteral", "identifierLiteral", "memberExpression", "valuePostfix", 
      "argumentList", "valueAtom", "variables", "variableDeclaration", "variableDeclarationWithoutAssignment", 
      "variableReAssignment", "variableDataType", "arrays", "arrayAccess", 
      "arrayIndexList", "arrayDeclaration", "arrayValues", "arrayItemsWithBrackets", 
      "arrayItem", "arrayElement", "arrayReAssignment", "arrayType", "arrayDeclarationTypeSizes", 
      "arrayDataType", "ifStatement", "elseIfStatement", "ifStatementCondition", 
      "elseStatement", "ifStatementBody", "importStatement", "importStatementWithBrackets", 
      "importStatementWithoutBrackets"
    },
    std::vector<std::string>{
      "", "'regex'", "'dict'", "'bool'", "'str'", "", "", "", "'if'", "'else'", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "'import'", "'from'"
    },
    std::vector<std::string>{
      "", "REGEX_TYPE", "DICT_KEYWORD", "BOOLEAN_TYPES", "STRING_TYPES", 
      "INTEGER_TYPES", "UNSIGNED_INTEGER_TYPES", "FLOAT_TYPES", "IF", "ELSE", 
      "NONE", "BOOLEAN", "IDENTIFIER", "PLUS", "MINUS", "MUL", "DIV", "MOD", 
      "EQ", "EQEQ", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", 
      "RBRACKET", "DOT", "COMMA", "AMPERSAND", "ANDAND", "OROR", "LT", "LTE", 
      "GT", "GTE", "NEQ", "COLON", "QUESTION", "BIT_OR", "BIT_XOR", "BIT_NOT", 
      "SHL", "SHR", "NEWLINE", "NEWLINE_VISIBLE", "WS_VISIBLE", "COMMENT", 
      "BLOCK_COMMENT", "WS", "FLOAT", "INTEGER", "STRING", "FORMATTED_STRING_START", 
      "IMPORT", "FROM", "FORMATTED_STRING_TEXT", "REGEX_LITERAL", "LBRACE_IN_FSTRING", 
      "FORMATTED_STRING_END", "RBRACE_IN_FSTRING", "EXPR_WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,61,569,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,1,0,5,
  	0,128,8,0,10,0,12,0,131,9,0,1,0,1,0,5,0,135,8,0,10,0,12,0,138,9,0,5,0,
  	140,8,0,10,0,12,0,143,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	3,1,156,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,169,8,2,5,
  	2,171,8,2,10,2,12,2,174,9,2,3,2,176,8,2,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,
  	4,1,4,1,4,1,5,1,5,3,5,190,8,5,1,6,1,6,1,6,3,6,195,8,6,1,6,1,6,1,7,1,7,
  	1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,3,9,209,8,9,1,10,1,10,1,10,5,10,214,8,
  	10,10,10,12,10,217,9,10,1,11,1,11,1,11,5,11,222,8,11,10,11,12,11,225,
  	9,11,1,12,1,12,1,12,5,12,230,8,12,10,12,12,12,233,9,12,1,13,1,13,1,13,
  	5,13,238,8,13,10,13,12,13,241,9,13,1,14,1,14,1,14,5,14,246,8,14,10,14,
  	12,14,249,9,14,1,15,1,15,1,15,5,15,254,8,15,10,15,12,15,257,9,15,1,16,
  	1,16,1,16,5,16,262,8,16,10,16,12,16,265,9,16,1,17,1,17,1,17,5,17,270,
  	8,17,10,17,12,17,273,9,17,1,18,1,18,1,18,5,18,278,8,18,10,18,12,18,281,
  	9,18,1,19,1,19,1,19,5,19,286,8,19,10,19,12,19,289,9,19,1,20,1,20,1,20,
  	1,20,3,20,295,8,20,1,21,1,21,5,21,299,8,21,10,21,12,21,302,9,21,1,21,
  	1,21,1,21,3,21,307,8,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,3,22,
  	317,8,22,1,23,1,23,1,23,1,23,3,23,323,8,23,1,24,1,24,3,24,327,8,24,1,
  	25,1,25,1,25,3,25,332,8,25,1,26,1,26,5,26,336,8,26,10,26,12,26,339,9,
  	26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,3,27,349,8,27,1,28,1,28,1,
  	29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,33,1,33,1,34,1,34,5,34,365,8,
  	34,10,34,12,34,368,9,34,1,35,1,35,1,35,1,35,3,35,374,8,35,1,35,3,35,377,
  	8,35,1,36,1,36,1,36,5,36,382,8,36,10,36,12,36,385,9,36,1,37,1,37,1,37,
  	1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,401,8,37,
  	1,38,1,38,1,38,3,38,406,8,38,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,40,
  	1,40,1,40,1,41,1,41,1,41,1,41,1,42,1,42,1,43,1,43,1,43,3,43,427,8,43,
  	1,44,1,44,1,44,1,44,1,44,1,45,1,45,1,45,5,45,437,8,45,10,45,12,45,440,
  	9,45,1,46,1,46,1,46,1,46,3,46,446,8,46,1,47,1,47,5,47,450,8,47,10,47,
  	12,47,453,9,47,1,47,3,47,456,8,47,1,48,1,48,1,48,1,48,5,48,462,8,48,10,
  	48,12,48,465,9,48,3,48,467,8,48,1,48,1,48,1,49,1,49,3,49,473,8,49,1,50,
  	1,50,1,50,1,50,1,50,1,50,1,50,1,50,3,50,483,8,50,1,51,1,51,1,51,1,51,
  	1,52,1,52,1,52,3,52,492,8,52,1,52,3,52,495,8,52,1,53,1,53,1,53,5,53,500,
  	8,53,10,53,12,53,503,9,53,1,54,1,54,1,55,1,55,1,55,1,55,1,55,1,55,5,55,
  	513,8,55,10,55,12,55,516,9,55,1,55,3,55,519,8,55,1,56,1,56,1,56,1,56,
  	3,56,525,8,56,1,56,1,56,1,56,1,57,1,57,1,58,1,58,1,58,1,59,1,59,5,59,
  	537,8,59,10,59,12,59,540,9,59,1,59,1,59,1,60,1,60,3,60,546,8,60,1,61,
  	1,61,1,61,1,61,1,61,5,61,553,8,61,10,61,12,61,556,9,61,3,61,558,8,61,
  	1,61,1,61,1,61,1,61,1,62,1,62,1,62,1,62,1,62,1,62,0,0,63,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,
  	58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,
  	104,106,108,110,112,114,116,118,120,122,124,0,7,1,0,3,7,2,0,19,19,36,
  	36,1,0,32,35,1,0,42,43,1,0,13,14,1,0,15,17,2,0,1,1,3,7,586,0,129,1,0,
  	0,0,2,155,1,0,0,0,4,157,1,0,0,0,6,179,1,0,0,0,8,183,1,0,0,0,10,189,1,
  	0,0,0,12,191,1,0,0,0,14,198,1,0,0,0,16,200,1,0,0,0,18,202,1,0,0,0,20,
  	210,1,0,0,0,22,218,1,0,0,0,24,226,1,0,0,0,26,234,1,0,0,0,28,242,1,0,0,
  	0,30,250,1,0,0,0,32,258,1,0,0,0,34,266,1,0,0,0,36,274,1,0,0,0,38,282,
  	1,0,0,0,40,290,1,0,0,0,42,306,1,0,0,0,44,316,1,0,0,0,46,322,1,0,0,0,48,
  	326,1,0,0,0,50,331,1,0,0,0,52,333,1,0,0,0,54,348,1,0,0,0,56,350,1,0,0,
  	0,58,352,1,0,0,0,60,354,1,0,0,0,62,356,1,0,0,0,64,358,1,0,0,0,66,360,
  	1,0,0,0,68,362,1,0,0,0,70,376,1,0,0,0,72,378,1,0,0,0,74,400,1,0,0,0,76,
  	405,1,0,0,0,78,407,1,0,0,0,80,414,1,0,0,0,82,417,1,0,0,0,84,421,1,0,0,
  	0,86,426,1,0,0,0,88,428,1,0,0,0,90,433,1,0,0,0,92,441,1,0,0,0,94,455,
  	1,0,0,0,96,457,1,0,0,0,98,472,1,0,0,0,100,482,1,0,0,0,102,484,1,0,0,0,
  	104,488,1,0,0,0,106,496,1,0,0,0,108,504,1,0,0,0,110,506,1,0,0,0,112,520,
  	1,0,0,0,114,529,1,0,0,0,116,531,1,0,0,0,118,534,1,0,0,0,120,545,1,0,0,
  	0,122,547,1,0,0,0,124,563,1,0,0,0,126,128,5,44,0,0,127,126,1,0,0,0,128,
  	131,1,0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,141,1,0,0,0,131,129,1,
  	0,0,0,132,136,3,2,1,0,133,135,5,44,0,0,134,133,1,0,0,0,135,138,1,0,0,
  	0,136,134,1,0,0,0,136,137,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,139,
  	132,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,1,0,0,0,142,144,1,
  	0,0,0,143,141,1,0,0,0,144,145,5,0,0,1,145,1,1,0,0,0,146,156,3,16,8,0,
  	147,156,3,76,38,0,148,156,3,86,43,0,149,156,3,4,2,0,150,156,3,68,34,0,
  	151,156,3,110,55,0,152,156,3,62,31,0,153,156,3,64,32,0,154,156,3,120,
  	60,0,155,146,1,0,0,0,155,147,1,0,0,0,155,148,1,0,0,0,155,149,1,0,0,0,
  	155,150,1,0,0,0,155,151,1,0,0,0,155,152,1,0,0,0,155,153,1,0,0,0,155,154,
  	1,0,0,0,156,3,1,0,0,0,157,158,5,2,0,0,158,159,5,32,0,0,159,160,3,8,4,
  	0,160,161,5,34,0,0,161,162,5,12,0,0,162,163,5,18,0,0,163,175,5,23,0,0,
  	164,172,3,6,3,0,165,166,5,28,0,0,166,168,3,6,3,0,167,169,5,28,0,0,168,
  	167,1,0,0,0,168,169,1,0,0,0,169,171,1,0,0,0,170,165,1,0,0,0,171,174,1,
  	0,0,0,172,170,1,0,0,0,172,173,1,0,0,0,173,176,1,0,0,0,174,172,1,0,0,0,
  	175,164,1,0,0,0,175,176,1,0,0,0,176,177,1,0,0,0,177,178,5,24,0,0,178,
  	5,1,0,0,0,179,180,3,46,23,0,180,181,5,37,0,0,181,182,3,16,8,0,182,7,1,
  	0,0,0,183,184,3,10,5,0,184,185,5,28,0,0,185,186,3,10,5,0,186,9,1,0,0,
  	0,187,190,3,12,6,0,188,190,3,14,7,0,189,187,1,0,0,0,189,188,1,0,0,0,190,
  	11,1,0,0,0,191,192,3,14,7,0,192,194,5,25,0,0,193,195,3,16,8,0,194,193,
  	1,0,0,0,194,195,1,0,0,0,195,196,1,0,0,0,196,197,5,26,0,0,197,13,1,0,0,
  	0,198,199,7,0,0,0,199,15,1,0,0,0,200,201,3,18,9,0,201,17,1,0,0,0,202,
  	208,3,20,10,0,203,204,5,38,0,0,204,205,3,16,8,0,205,206,5,37,0,0,206,
  	207,3,16,8,0,207,209,1,0,0,0,208,203,1,0,0,0,208,209,1,0,0,0,209,19,1,
  	0,0,0,210,215,3,22,11,0,211,212,5,31,0,0,212,214,3,22,11,0,213,211,1,
  	0,0,0,214,217,1,0,0,0,215,213,1,0,0,0,215,216,1,0,0,0,216,21,1,0,0,0,
  	217,215,1,0,0,0,218,223,3,24,12,0,219,220,5,30,0,0,220,222,3,24,12,0,
  	221,219,1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,23,
  	1,0,0,0,225,223,1,0,0,0,226,231,3,26,13,0,227,228,5,39,0,0,228,230,3,
  	26,13,0,229,227,1,0,0,0,230,233,1,0,0,0,231,229,1,0,0,0,231,232,1,0,0,
  	0,232,25,1,0,0,0,233,231,1,0,0,0,234,239,3,28,14,0,235,236,5,40,0,0,236,
  	238,3,28,14,0,237,235,1,0,0,0,238,241,1,0,0,0,239,237,1,0,0,0,239,240,
  	1,0,0,0,240,27,1,0,0,0,241,239,1,0,0,0,242,247,3,30,15,0,243,244,5,29,
  	0,0,244,246,3,30,15,0,245,243,1,0,0,0,246,249,1,0,0,0,247,245,1,0,0,0,
  	247,248,1,0,0,0,248,29,1,0,0,0,249,247,1,0,0,0,250,255,3,32,16,0,251,
  	252,7,1,0,0,252,254,3,32,16,0,253,251,1,0,0,0,254,257,1,0,0,0,255,253,
  	1,0,0,0,255,256,1,0,0,0,256,31,1,0,0,0,257,255,1,0,0,0,258,263,3,34,17,
  	0,259,260,7,2,0,0,260,262,3,34,17,0,261,259,1,0,0,0,262,265,1,0,0,0,263,
  	261,1,0,0,0,263,264,1,0,0,0,264,33,1,0,0,0,265,263,1,0,0,0,266,271,3,
  	36,18,0,267,268,7,3,0,0,268,270,3,36,18,0,269,267,1,0,0,0,270,273,1,0,
  	0,0,271,269,1,0,0,0,271,272,1,0,0,0,272,35,1,0,0,0,273,271,1,0,0,0,274,
  	279,3,38,19,0,275,276,7,4,0,0,276,278,3,38,19,0,277,275,1,0,0,0,278,281,
  	1,0,0,0,279,277,1,0,0,0,279,280,1,0,0,0,280,37,1,0,0,0,281,279,1,0,0,
  	0,282,287,3,40,20,0,283,284,7,5,0,0,284,286,3,40,20,0,285,283,1,0,0,0,
  	286,289,1,0,0,0,287,285,1,0,0,0,287,288,1,0,0,0,288,39,1,0,0,0,289,287,
  	1,0,0,0,290,294,3,42,21,0,291,292,5,15,0,0,292,293,5,15,0,0,293,295,3,
  	40,20,0,294,291,1,0,0,0,294,295,1,0,0,0,295,41,1,0,0,0,296,300,5,20,0,
  	0,297,299,5,20,0,0,298,297,1,0,0,0,299,302,1,0,0,0,300,298,1,0,0,0,300,
  	301,1,0,0,0,301,307,1,0,0,0,302,300,1,0,0,0,303,307,5,41,0,0,304,307,
  	5,13,0,0,305,307,5,14,0,0,306,296,1,0,0,0,306,303,1,0,0,0,306,304,1,0,
  	0,0,306,305,1,0,0,0,306,307,1,0,0,0,307,308,1,0,0,0,308,309,3,44,22,0,
  	309,43,1,0,0,0,310,311,5,21,0,0,311,312,3,16,8,0,312,313,5,22,0,0,313,
  	317,1,0,0,0,314,317,3,46,23,0,315,317,3,68,34,0,316,310,1,0,0,0,316,314,
  	1,0,0,0,316,315,1,0,0,0,317,45,1,0,0,0,318,323,3,48,24,0,319,323,3,50,
  	25,0,320,323,3,62,31,0,321,323,3,66,33,0,322,318,1,0,0,0,322,319,1,0,
  	0,0,322,320,1,0,0,0,322,321,1,0,0,0,323,47,1,0,0,0,324,327,3,60,30,0,
  	325,327,3,58,29,0,326,324,1,0,0,0,326,325,1,0,0,0,327,49,1,0,0,0,328,
  	332,3,56,28,0,329,332,3,52,26,0,330,332,3,66,33,0,331,328,1,0,0,0,331,
  	329,1,0,0,0,331,330,1,0,0,0,332,51,1,0,0,0,333,337,5,53,0,0,334,336,3,
  	54,27,0,335,334,1,0,0,0,336,339,1,0,0,0,337,335,1,0,0,0,337,338,1,0,0,
  	0,338,340,1,0,0,0,339,337,1,0,0,0,340,341,5,59,0,0,341,53,1,0,0,0,342,
  	349,5,57,0,0,343,349,5,56,0,0,344,345,5,58,0,0,345,346,3,16,8,0,346,347,
  	5,60,0,0,347,349,1,0,0,0,348,342,1,0,0,0,348,343,1,0,0,0,348,344,1,0,
  	0,0,349,55,1,0,0,0,350,351,5,52,0,0,351,57,1,0,0,0,352,353,5,50,0,0,353,
  	59,1,0,0,0,354,355,5,51,0,0,355,61,1,0,0,0,356,357,5,11,0,0,357,63,1,
  	0,0,0,358,359,5,10,0,0,359,65,1,0,0,0,360,361,5,12,0,0,361,67,1,0,0,0,
  	362,366,3,74,37,0,363,365,3,70,35,0,364,363,1,0,0,0,365,368,1,0,0,0,366,
  	364,1,0,0,0,366,367,1,0,0,0,367,69,1,0,0,0,368,366,1,0,0,0,369,370,5,
  	27,0,0,370,377,3,66,33,0,371,373,5,21,0,0,372,374,3,72,36,0,373,372,1,
  	0,0,0,373,374,1,0,0,0,374,375,1,0,0,0,375,377,5,22,0,0,376,369,1,0,0,
  	0,376,371,1,0,0,0,377,71,1,0,0,0,378,383,3,16,8,0,379,380,5,28,0,0,380,
  	382,3,16,8,0,381,379,1,0,0,0,382,385,1,0,0,0,383,381,1,0,0,0,383,384,
  	1,0,0,0,384,73,1,0,0,0,385,383,1,0,0,0,386,401,3,66,33,0,387,401,3,56,
  	28,0,388,389,5,21,0,0,389,390,3,62,31,0,390,391,5,22,0,0,391,401,1,0,
  	0,0,392,393,5,21,0,0,393,394,3,48,24,0,394,395,5,22,0,0,395,401,1,0,0,
  	0,396,397,5,21,0,0,397,398,3,16,8,0,398,399,5,22,0,0,399,401,1,0,0,0,
  	400,386,1,0,0,0,400,387,1,0,0,0,400,388,1,0,0,0,400,392,1,0,0,0,400,396,
  	1,0,0,0,401,75,1,0,0,0,402,406,3,78,39,0,403,406,3,80,40,0,404,406,3,
  	82,41,0,405,402,1,0,0,0,405,403,1,0,0,0,405,404,1,0,0,0,406,77,1,0,0,
  	0,407,408,3,84,42,0,408,409,5,12,0,0,409,410,5,18,0,0,410,411,6,39,-1,
  	0,411,412,3,16,8,0,412,413,6,39,-1,0,413,79,1,0,0,0,414,415,3,84,42,0,
  	415,416,5,12,0,0,416,81,1,0,0,0,417,418,5,12,0,0,418,419,5,18,0,0,419,
  	420,3,16,8,0,420,83,1,0,0,0,421,422,7,6,0,0,422,85,1,0,0,0,423,427,3,
  	92,46,0,424,427,3,102,51,0,425,427,3,88,44,0,426,423,1,0,0,0,426,424,
  	1,0,0,0,426,425,1,0,0,0,427,87,1,0,0,0,428,429,5,12,0,0,429,430,5,25,
  	0,0,430,431,3,90,45,0,431,432,5,26,0,0,432,89,1,0,0,0,433,438,3,16,8,
  	0,434,435,5,28,0,0,435,437,3,16,8,0,436,434,1,0,0,0,437,440,1,0,0,0,438,
  	436,1,0,0,0,438,439,1,0,0,0,439,91,1,0,0,0,440,438,1,0,0,0,441,442,3,
  	104,52,0,442,445,5,12,0,0,443,444,5,18,0,0,444,446,3,94,47,0,445,443,
  	1,0,0,0,445,446,1,0,0,0,446,93,1,0,0,0,447,456,3,96,48,0,448,450,3,16,
  	8,0,449,448,1,0,0,0,450,453,1,0,0,0,451,449,1,0,0,0,451,452,1,0,0,0,452,
  	456,1,0,0,0,453,451,1,0,0,0,454,456,3,68,34,0,455,447,1,0,0,0,455,451,
  	1,0,0,0,455,454,1,0,0,0,456,95,1,0,0,0,457,466,5,25,0,0,458,463,3,98,
  	49,0,459,460,5,28,0,0,460,462,3,98,49,0,461,459,1,0,0,0,462,465,1,0,0,
  	0,463,461,1,0,0,0,463,464,1,0,0,0,464,467,1,0,0,0,465,463,1,0,0,0,466,
  	458,1,0,0,0,466,467,1,0,0,0,467,468,1,0,0,0,468,469,5,26,0,0,469,97,1,
  	0,0,0,470,473,3,96,48,0,471,473,3,100,50,0,472,470,1,0,0,0,472,471,1,
  	0,0,0,473,99,1,0,0,0,474,483,3,56,28,0,475,483,3,52,26,0,476,483,3,66,
  	33,0,477,483,3,60,30,0,478,483,3,58,29,0,479,483,3,62,31,0,480,483,3,
  	64,32,0,481,483,3,16,8,0,482,474,1,0,0,0,482,475,1,0,0,0,482,476,1,0,
  	0,0,482,477,1,0,0,0,482,478,1,0,0,0,482,479,1,0,0,0,482,480,1,0,0,0,482,
  	481,1,0,0,0,483,101,1,0,0,0,484,485,5,12,0,0,485,486,5,18,0,0,486,487,
  	3,96,48,0,487,103,1,0,0,0,488,494,3,108,54,0,489,491,5,25,0,0,490,492,
  	3,106,53,0,491,490,1,0,0,0,491,492,1,0,0,0,492,493,1,0,0,0,493,495,5,
  	26,0,0,494,489,1,0,0,0,494,495,1,0,0,0,495,105,1,0,0,0,496,501,3,16,8,
  	0,497,498,5,28,0,0,498,500,3,16,8,0,499,497,1,0,0,0,500,503,1,0,0,0,501,
  	499,1,0,0,0,501,502,1,0,0,0,502,107,1,0,0,0,503,501,1,0,0,0,504,505,7,
  	0,0,0,505,109,1,0,0,0,506,507,5,8,0,0,507,508,5,21,0,0,508,509,3,114,
  	57,0,509,510,5,22,0,0,510,514,3,118,59,0,511,513,3,112,56,0,512,511,1,
  	0,0,0,513,516,1,0,0,0,514,512,1,0,0,0,514,515,1,0,0,0,515,518,1,0,0,0,
  	516,514,1,0,0,0,517,519,3,116,58,0,518,517,1,0,0,0,518,519,1,0,0,0,519,
  	111,1,0,0,0,520,521,5,9,0,0,521,522,5,8,0,0,522,524,5,21,0,0,523,525,
  	3,114,57,0,524,523,1,0,0,0,524,525,1,0,0,0,525,526,1,0,0,0,526,527,5,
  	22,0,0,527,528,3,118,59,0,528,113,1,0,0,0,529,530,3,16,8,0,530,115,1,
  	0,0,0,531,532,5,9,0,0,532,533,3,118,59,0,533,117,1,0,0,0,534,538,5,23,
  	0,0,535,537,3,2,1,0,536,535,1,0,0,0,537,540,1,0,0,0,538,536,1,0,0,0,538,
  	539,1,0,0,0,539,541,1,0,0,0,540,538,1,0,0,0,541,542,5,24,0,0,542,119,
  	1,0,0,0,543,546,3,122,61,0,544,546,3,124,62,0,545,543,1,0,0,0,545,544,
  	1,0,0,0,546,121,1,0,0,0,547,548,5,54,0,0,548,557,5,25,0,0,549,554,3,66,
  	33,0,550,551,5,28,0,0,551,553,3,66,33,0,552,550,1,0,0,0,553,556,1,0,0,
  	0,554,552,1,0,0,0,554,555,1,0,0,0,555,558,1,0,0,0,556,554,1,0,0,0,557,
  	549,1,0,0,0,557,558,1,0,0,0,558,559,1,0,0,0,559,560,5,26,0,0,560,561,
  	5,55,0,0,561,562,3,56,28,0,562,123,1,0,0,0,563,564,5,54,0,0,564,565,3,
  	66,33,0,565,566,5,55,0,0,566,567,3,56,28,0,567,125,1,0,0,0,54,129,136,
  	141,155,168,172,175,189,194,208,215,223,231,239,247,255,263,271,279,287,
  	294,300,306,316,322,326,331,337,348,366,373,376,383,400,405,426,438,445,
  	451,455,463,466,472,482,491,494,501,514,518,524,538,545,554,557
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  grammarParserStaticData = std::move(staticData);
}

}

Grammar::Grammar(TokenStream *input) : Grammar(input, antlr4::atn::ParserATNSimulatorOptions()) {}

Grammar::Grammar(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  Grammar::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *grammarParserStaticData->atn, grammarParserStaticData->decisionToDFA, grammarParserStaticData->sharedContextCache, options);
}

Grammar::~Grammar() {
  delete _interpreter;
}

const atn::ATN& Grammar::getATN() const {
  return *grammarParserStaticData->atn;
}

std::string Grammar::getGrammarFileName() const {
  return "Grammar.g4";
}

const std::vector<std::string>& Grammar::getRuleNames() const {
  return grammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& Grammar::getVocabulary() const {
  return grammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView Grammar::getSerializedATN() const {
  return grammarParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

Grammar::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ProgramContext::EOF() {
  return getToken(Grammar::EOF, 0);
}

std::vector<tree::TerminalNode *> Grammar::ProgramContext::NEWLINE() {
  return getTokens(Grammar::NEWLINE);
}

tree::TerminalNode* Grammar::ProgramContext::NEWLINE(size_t i) {
  return getToken(Grammar::NEWLINE, i);
}

std::vector<Grammar::StatementsContext *> Grammar::ProgramContext::statements() {
  return getRuleContexts<Grammar::StatementsContext>();
}

Grammar::StatementsContext* Grammar::ProgramContext::statements(size_t i) {
  return getRuleContext<Grammar::StatementsContext>(i);
}


size_t Grammar::ProgramContext::getRuleIndex() const {
  return Grammar::RuleProgram;
}

void Grammar::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void Grammar::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any Grammar::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ProgramContext* Grammar::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, Grammar::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::NEWLINE) {
      setState(126);
      match(Grammar::NEWLINE);
      setState(131);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34905096138554878) != 0)) {
      setState(132);
      statements();
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::NEWLINE) {
        setState(133);
        match(Grammar::NEWLINE);
        setState(138);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(144);
    match(Grammar::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

Grammar::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ExpressionContext* Grammar::StatementsContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}

Grammar::VariablesContext* Grammar::StatementsContext::variables() {
  return getRuleContext<Grammar::VariablesContext>(0);
}

Grammar::ArraysContext* Grammar::StatementsContext::arrays() {
  return getRuleContext<Grammar::ArraysContext>(0);
}

Grammar::DictionaryDeclarationContext* Grammar::StatementsContext::dictionaryDeclaration() {
  return getRuleContext<Grammar::DictionaryDeclarationContext>(0);
}

Grammar::MemberExpressionContext* Grammar::StatementsContext::memberExpression() {
  return getRuleContext<Grammar::MemberExpressionContext>(0);
}

Grammar::IfStatementContext* Grammar::StatementsContext::ifStatement() {
  return getRuleContext<Grammar::IfStatementContext>(0);
}

Grammar::BooleanLiteralContext* Grammar::StatementsContext::booleanLiteral() {
  return getRuleContext<Grammar::BooleanLiteralContext>(0);
}

Grammar::NoneLiteralContext* Grammar::StatementsContext::noneLiteral() {
  return getRuleContext<Grammar::NoneLiteralContext>(0);
}

Grammar::ImportStatementContext* Grammar::StatementsContext::importStatement() {
  return getRuleContext<Grammar::ImportStatementContext>(0);
}


size_t Grammar::StatementsContext::getRuleIndex() const {
  return Grammar::RuleStatements;
}

void Grammar::StatementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatements(this);
}

void Grammar::StatementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatements(this);
}


std::any Grammar::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

Grammar::StatementsContext* Grammar::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 2, Grammar::RuleStatements);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(155);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(146);
      expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(147);
      variables();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(148);
      arrays();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(149);
      dictionaryDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(150);
      memberExpression();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(151);
      ifStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(152);
      booleanLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(153);
      noneLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(154);
      importStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryDeclarationContext ------------------------------------------------------------------

Grammar::DictionaryDeclarationContext::DictionaryDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::DICT_KEYWORD() {
  return getToken(Grammar::DICT_KEYWORD, 0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::LT() {
  return getToken(Grammar::LT, 0);
}

Grammar::DictionaryDeclarationTypeContext* Grammar::DictionaryDeclarationContext::dictionaryDeclarationType() {
  return getRuleContext<Grammar::DictionaryDeclarationTypeContext>(0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::GT() {
  return getToken(Grammar::GT, 0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::EQ() {
  return getToken(Grammar::EQ, 0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::LBRACE() {
  return getToken(Grammar::LBRACE, 0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::RBRACE() {
  return getToken(Grammar::RBRACE, 0);
}

std::vector<Grammar::DictionaryAssignmentBodyContext *> Grammar::DictionaryDeclarationContext::dictionaryAssignmentBody() {
  return getRuleContexts<Grammar::DictionaryAssignmentBodyContext>();
}

Grammar::DictionaryAssignmentBodyContext* Grammar::DictionaryDeclarationContext::dictionaryAssignmentBody(size_t i) {
  return getRuleContext<Grammar::DictionaryAssignmentBodyContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::DictionaryDeclarationContext::COMMA() {
  return getTokens(Grammar::COMMA);
}

tree::TerminalNode* Grammar::DictionaryDeclarationContext::COMMA(size_t i) {
  return getToken(Grammar::COMMA, i);
}


size_t Grammar::DictionaryDeclarationContext::getRuleIndex() const {
  return Grammar::RuleDictionaryDeclaration;
}

void Grammar::DictionaryDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionaryDeclaration(this);
}

void Grammar::DictionaryDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionaryDeclaration(this);
}


std::any Grammar::DictionaryDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDictionaryDeclaration(this);
  else
    return visitor->visitChildren(this);
}

Grammar::DictionaryDeclarationContext* Grammar::dictionaryDeclaration() {
  DictionaryDeclarationContext *_localctx = _tracker.createInstance<DictionaryDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, Grammar::RuleDictionaryDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    match(Grammar::DICT_KEYWORD);
    setState(158);
    match(Grammar::LT);
    setState(159);
    dictionaryDeclarationType();
    setState(160);
    match(Grammar::GT);
    setState(161);
    match(Grammar::IDENTIFIER);
    setState(162);
    match(Grammar::EQ);
    setState(163);
    match(Grammar::LBRACE);
    setState(175);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16888498602645504) != 0)) {
      setState(164);
      dictionaryAssignmentBody();
      setState(172);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::COMMA) {
        setState(165);
        match(Grammar::COMMA);
        setState(166);
        dictionaryAssignmentBody();
        setState(168);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          setState(167);
          match(Grammar::COMMA);
          break;
        }

        default:
          break;
        }
        setState(174);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(177);
    match(Grammar::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryAssignmentBodyContext ------------------------------------------------------------------

Grammar::DictionaryAssignmentBodyContext::DictionaryAssignmentBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::LiteralsContext* Grammar::DictionaryAssignmentBodyContext::literals() {
  return getRuleContext<Grammar::LiteralsContext>(0);
}

tree::TerminalNode* Grammar::DictionaryAssignmentBodyContext::COLON() {
  return getToken(Grammar::COLON, 0);
}

Grammar::ExpressionContext* Grammar::DictionaryAssignmentBodyContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::DictionaryAssignmentBodyContext::getRuleIndex() const {
  return Grammar::RuleDictionaryAssignmentBody;
}

void Grammar::DictionaryAssignmentBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionaryAssignmentBody(this);
}

void Grammar::DictionaryAssignmentBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionaryAssignmentBody(this);
}


std::any Grammar::DictionaryAssignmentBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDictionaryAssignmentBody(this);
  else
    return visitor->visitChildren(this);
}

Grammar::DictionaryAssignmentBodyContext* Grammar::dictionaryAssignmentBody() {
  DictionaryAssignmentBodyContext *_localctx = _tracker.createInstance<DictionaryAssignmentBodyContext>(_ctx, getState());
  enterRule(_localctx, 6, Grammar::RuleDictionaryAssignmentBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    literals();
    setState(180);
    match(Grammar::COLON);
    setState(181);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryDeclarationTypeContext ------------------------------------------------------------------

Grammar::DictionaryDeclarationTypeContext::DictionaryDeclarationTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::DictionaryTypeElementContext *> Grammar::DictionaryDeclarationTypeContext::dictionaryTypeElement() {
  return getRuleContexts<Grammar::DictionaryTypeElementContext>();
}

Grammar::DictionaryTypeElementContext* Grammar::DictionaryDeclarationTypeContext::dictionaryTypeElement(size_t i) {
  return getRuleContext<Grammar::DictionaryTypeElementContext>(i);
}

tree::TerminalNode* Grammar::DictionaryDeclarationTypeContext::COMMA() {
  return getToken(Grammar::COMMA, 0);
}


size_t Grammar::DictionaryDeclarationTypeContext::getRuleIndex() const {
  return Grammar::RuleDictionaryDeclarationType;
}

void Grammar::DictionaryDeclarationTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionaryDeclarationType(this);
}

void Grammar::DictionaryDeclarationTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionaryDeclarationType(this);
}


std::any Grammar::DictionaryDeclarationTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDictionaryDeclarationType(this);
  else
    return visitor->visitChildren(this);
}

Grammar::DictionaryDeclarationTypeContext* Grammar::dictionaryDeclarationType() {
  DictionaryDeclarationTypeContext *_localctx = _tracker.createInstance<DictionaryDeclarationTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, Grammar::RuleDictionaryDeclarationType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    dictionaryTypeElement();
    setState(184);
    match(Grammar::COMMA);
    setState(185);
    dictionaryTypeElement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryTypeElementContext ------------------------------------------------------------------

Grammar::DictionaryTypeElementContext::DictionaryTypeElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::DictionaryDeclarationTypeArrayContext* Grammar::DictionaryTypeElementContext::dictionaryDeclarationTypeArray() {
  return getRuleContext<Grammar::DictionaryDeclarationTypeArrayContext>(0);
}

Grammar::DictionaryDataTypeContext* Grammar::DictionaryTypeElementContext::dictionaryDataType() {
  return getRuleContext<Grammar::DictionaryDataTypeContext>(0);
}


size_t Grammar::DictionaryTypeElementContext::getRuleIndex() const {
  return Grammar::RuleDictionaryTypeElement;
}

void Grammar::DictionaryTypeElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionaryTypeElement(this);
}

void Grammar::DictionaryTypeElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionaryTypeElement(this);
}


std::any Grammar::DictionaryTypeElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDictionaryTypeElement(this);
  else
    return visitor->visitChildren(this);
}

Grammar::DictionaryTypeElementContext* Grammar::dictionaryTypeElement() {
  DictionaryTypeElementContext *_localctx = _tracker.createInstance<DictionaryTypeElementContext>(_ctx, getState());
  enterRule(_localctx, 10, Grammar::RuleDictionaryTypeElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(189);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(187);
      dictionaryDeclarationTypeArray();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(188);
      dictionaryDataType();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryDeclarationTypeArrayContext ------------------------------------------------------------------

Grammar::DictionaryDeclarationTypeArrayContext::DictionaryDeclarationTypeArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::DictionaryDataTypeContext* Grammar::DictionaryDeclarationTypeArrayContext::dictionaryDataType() {
  return getRuleContext<Grammar::DictionaryDataTypeContext>(0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationTypeArrayContext::LBRACKET() {
  return getToken(Grammar::LBRACKET, 0);
}

tree::TerminalNode* Grammar::DictionaryDeclarationTypeArrayContext::RBRACKET() {
  return getToken(Grammar::RBRACKET, 0);
}

Grammar::ExpressionContext* Grammar::DictionaryDeclarationTypeArrayContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::DictionaryDeclarationTypeArrayContext::getRuleIndex() const {
  return Grammar::RuleDictionaryDeclarationTypeArray;
}

void Grammar::DictionaryDeclarationTypeArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionaryDeclarationTypeArray(this);
}

void Grammar::DictionaryDeclarationTypeArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionaryDeclarationTypeArray(this);
}


std::any Grammar::DictionaryDeclarationTypeArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDictionaryDeclarationTypeArray(this);
  else
    return visitor->visitChildren(this);
}

Grammar::DictionaryDeclarationTypeArrayContext* Grammar::dictionaryDeclarationTypeArray() {
  DictionaryDeclarationTypeArrayContext *_localctx = _tracker.createInstance<DictionaryDeclarationTypeArrayContext>(_ctx, getState());
  enterRule(_localctx, 12, Grammar::RuleDictionaryDeclarationTypeArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    dictionaryDataType();
    setState(192);
    match(Grammar::LBRACKET);
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16890697629071360) != 0)) {
      setState(193);
      expression();
    }
    setState(196);
    match(Grammar::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryDataTypeContext ------------------------------------------------------------------

Grammar::DictionaryDataTypeContext::DictionaryDataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::DictionaryDataTypeContext::INTEGER_TYPES() {
  return getToken(Grammar::INTEGER_TYPES, 0);
}

tree::TerminalNode* Grammar::DictionaryDataTypeContext::UNSIGNED_INTEGER_TYPES() {
  return getToken(Grammar::UNSIGNED_INTEGER_TYPES, 0);
}

tree::TerminalNode* Grammar::DictionaryDataTypeContext::FLOAT_TYPES() {
  return getToken(Grammar::FLOAT_TYPES, 0);
}

tree::TerminalNode* Grammar::DictionaryDataTypeContext::BOOLEAN_TYPES() {
  return getToken(Grammar::BOOLEAN_TYPES, 0);
}

tree::TerminalNode* Grammar::DictionaryDataTypeContext::STRING_TYPES() {
  return getToken(Grammar::STRING_TYPES, 0);
}


size_t Grammar::DictionaryDataTypeContext::getRuleIndex() const {
  return Grammar::RuleDictionaryDataType;
}

void Grammar::DictionaryDataTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictionaryDataType(this);
}

void Grammar::DictionaryDataTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictionaryDataType(this);
}


std::any Grammar::DictionaryDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitDictionaryDataType(this);
  else
    return visitor->visitChildren(this);
}

Grammar::DictionaryDataTypeContext* Grammar::dictionaryDataType() {
  DictionaryDataTypeContext *_localctx = _tracker.createInstance<DictionaryDataTypeContext>(_ctx, getState());
  enterRule(_localctx, 14, Grammar::RuleDictionaryDataType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

Grammar::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ConditionalExpressionContext* Grammar::ExpressionContext::conditionalExpression() {
  return getRuleContext<Grammar::ConditionalExpressionContext>(0);
}


size_t Grammar::ExpressionContext::getRuleIndex() const {
  return Grammar::RuleExpression;
}

void Grammar::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void Grammar::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any Grammar::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ExpressionContext* Grammar::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, Grammar::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(200);
    conditionalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

Grammar::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::LogicalOrExpressionContext* Grammar::ConditionalExpressionContext::logicalOrExpression() {
  return getRuleContext<Grammar::LogicalOrExpressionContext>(0);
}

tree::TerminalNode* Grammar::ConditionalExpressionContext::QUESTION() {
  return getToken(Grammar::QUESTION, 0);
}

std::vector<Grammar::ExpressionContext *> Grammar::ConditionalExpressionContext::expression() {
  return getRuleContexts<Grammar::ExpressionContext>();
}

Grammar::ExpressionContext* Grammar::ConditionalExpressionContext::expression(size_t i) {
  return getRuleContext<Grammar::ExpressionContext>(i);
}

tree::TerminalNode* Grammar::ConditionalExpressionContext::COLON() {
  return getToken(Grammar::COLON, 0);
}


size_t Grammar::ConditionalExpressionContext::getRuleIndex() const {
  return Grammar::RuleConditionalExpression;
}

void Grammar::ConditionalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpression(this);
}

void Grammar::ConditionalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpression(this);
}


std::any Grammar::ConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ConditionalExpressionContext* Grammar::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 18, Grammar::RuleConditionalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    logicalOrExpression();
    setState(208);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::QUESTION) {
      setState(203);
      match(Grammar::QUESTION);
      setState(204);
      expression();
      setState(205);
      match(Grammar::COLON);
      setState(206);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

Grammar::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::LogicalAndExpressionContext *> Grammar::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContexts<Grammar::LogicalAndExpressionContext>();
}

Grammar::LogicalAndExpressionContext* Grammar::LogicalOrExpressionContext::logicalAndExpression(size_t i) {
  return getRuleContext<Grammar::LogicalAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::LogicalOrExpressionContext::OROR() {
  return getTokens(Grammar::OROR);
}

tree::TerminalNode* Grammar::LogicalOrExpressionContext::OROR(size_t i) {
  return getToken(Grammar::OROR, i);
}


size_t Grammar::LogicalOrExpressionContext::getRuleIndex() const {
  return Grammar::RuleLogicalOrExpression;
}

void Grammar::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}

void Grammar::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}


std::any Grammar::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::LogicalOrExpressionContext* Grammar::logicalOrExpression() {
  LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 20, Grammar::RuleLogicalOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    logicalAndExpression();
    setState(215);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::OROR) {
      setState(211);
      match(Grammar::OROR);
      setState(212);
      logicalAndExpression();
      setState(217);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

Grammar::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::BitwiseOrExpressionContext *> Grammar::LogicalAndExpressionContext::bitwiseOrExpression() {
  return getRuleContexts<Grammar::BitwiseOrExpressionContext>();
}

Grammar::BitwiseOrExpressionContext* Grammar::LogicalAndExpressionContext::bitwiseOrExpression(size_t i) {
  return getRuleContext<Grammar::BitwiseOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::LogicalAndExpressionContext::ANDAND() {
  return getTokens(Grammar::ANDAND);
}

tree::TerminalNode* Grammar::LogicalAndExpressionContext::ANDAND(size_t i) {
  return getToken(Grammar::ANDAND, i);
}


size_t Grammar::LogicalAndExpressionContext::getRuleIndex() const {
  return Grammar::RuleLogicalAndExpression;
}

void Grammar::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}

void Grammar::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}


std::any Grammar::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::LogicalAndExpressionContext* Grammar::logicalAndExpression() {
  LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 22, Grammar::RuleLogicalAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    bitwiseOrExpression();
    setState(223);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::ANDAND) {
      setState(219);
      match(Grammar::ANDAND);
      setState(220);
      bitwiseOrExpression();
      setState(225);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseOrExpressionContext ------------------------------------------------------------------

Grammar::BitwiseOrExpressionContext::BitwiseOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::BitwiseXorExpressionContext *> Grammar::BitwiseOrExpressionContext::bitwiseXorExpression() {
  return getRuleContexts<Grammar::BitwiseXorExpressionContext>();
}

Grammar::BitwiseXorExpressionContext* Grammar::BitwiseOrExpressionContext::bitwiseXorExpression(size_t i) {
  return getRuleContext<Grammar::BitwiseXorExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::BitwiseOrExpressionContext::BIT_OR() {
  return getTokens(Grammar::BIT_OR);
}

tree::TerminalNode* Grammar::BitwiseOrExpressionContext::BIT_OR(size_t i) {
  return getToken(Grammar::BIT_OR, i);
}


size_t Grammar::BitwiseOrExpressionContext::getRuleIndex() const {
  return Grammar::RuleBitwiseOrExpression;
}

void Grammar::BitwiseOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseOrExpression(this);
}

void Grammar::BitwiseOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseOrExpression(this);
}


std::any Grammar::BitwiseOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitBitwiseOrExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::BitwiseOrExpressionContext* Grammar::bitwiseOrExpression() {
  BitwiseOrExpressionContext *_localctx = _tracker.createInstance<BitwiseOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 24, Grammar::RuleBitwiseOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    bitwiseXorExpression();
    setState(231);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::BIT_OR) {
      setState(227);
      match(Grammar::BIT_OR);
      setState(228);
      bitwiseXorExpression();
      setState(233);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseXorExpressionContext ------------------------------------------------------------------

Grammar::BitwiseXorExpressionContext::BitwiseXorExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::BitwiseAndExpressionContext *> Grammar::BitwiseXorExpressionContext::bitwiseAndExpression() {
  return getRuleContexts<Grammar::BitwiseAndExpressionContext>();
}

Grammar::BitwiseAndExpressionContext* Grammar::BitwiseXorExpressionContext::bitwiseAndExpression(size_t i) {
  return getRuleContext<Grammar::BitwiseAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::BitwiseXorExpressionContext::BIT_XOR() {
  return getTokens(Grammar::BIT_XOR);
}

tree::TerminalNode* Grammar::BitwiseXorExpressionContext::BIT_XOR(size_t i) {
  return getToken(Grammar::BIT_XOR, i);
}


size_t Grammar::BitwiseXorExpressionContext::getRuleIndex() const {
  return Grammar::RuleBitwiseXorExpression;
}

void Grammar::BitwiseXorExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseXorExpression(this);
}

void Grammar::BitwiseXorExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseXorExpression(this);
}


std::any Grammar::BitwiseXorExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitBitwiseXorExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::BitwiseXorExpressionContext* Grammar::bitwiseXorExpression() {
  BitwiseXorExpressionContext *_localctx = _tracker.createInstance<BitwiseXorExpressionContext>(_ctx, getState());
  enterRule(_localctx, 26, Grammar::RuleBitwiseXorExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    bitwiseAndExpression();
    setState(239);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::BIT_XOR) {
      setState(235);
      match(Grammar::BIT_XOR);
      setState(236);
      bitwiseAndExpression();
      setState(241);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseAndExpressionContext ------------------------------------------------------------------

Grammar::BitwiseAndExpressionContext::BitwiseAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::EqualityExpressionContext *> Grammar::BitwiseAndExpressionContext::equalityExpression() {
  return getRuleContexts<Grammar::EqualityExpressionContext>();
}

Grammar::EqualityExpressionContext* Grammar::BitwiseAndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<Grammar::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::BitwiseAndExpressionContext::AMPERSAND() {
  return getTokens(Grammar::AMPERSAND);
}

tree::TerminalNode* Grammar::BitwiseAndExpressionContext::AMPERSAND(size_t i) {
  return getToken(Grammar::AMPERSAND, i);
}


size_t Grammar::BitwiseAndExpressionContext::getRuleIndex() const {
  return Grammar::RuleBitwiseAndExpression;
}

void Grammar::BitwiseAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseAndExpression(this);
}

void Grammar::BitwiseAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseAndExpression(this);
}


std::any Grammar::BitwiseAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitBitwiseAndExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::BitwiseAndExpressionContext* Grammar::bitwiseAndExpression() {
  BitwiseAndExpressionContext *_localctx = _tracker.createInstance<BitwiseAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 28, Grammar::RuleBitwiseAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    equalityExpression();
    setState(247);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::AMPERSAND) {
      setState(243);
      match(Grammar::AMPERSAND);
      setState(244);
      equalityExpression();
      setState(249);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

Grammar::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::RelationalExpressionContext *> Grammar::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<Grammar::RelationalExpressionContext>();
}

Grammar::RelationalExpressionContext* Grammar::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<Grammar::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::EqualityExpressionContext::EQEQ() {
  return getTokens(Grammar::EQEQ);
}

tree::TerminalNode* Grammar::EqualityExpressionContext::EQEQ(size_t i) {
  return getToken(Grammar::EQEQ, i);
}

std::vector<tree::TerminalNode *> Grammar::EqualityExpressionContext::NEQ() {
  return getTokens(Grammar::NEQ);
}

tree::TerminalNode* Grammar::EqualityExpressionContext::NEQ(size_t i) {
  return getToken(Grammar::NEQ, i);
}


size_t Grammar::EqualityExpressionContext::getRuleIndex() const {
  return Grammar::RuleEqualityExpression;
}

void Grammar::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void Grammar::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


std::any Grammar::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::EqualityExpressionContext* Grammar::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, Grammar::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    relationalExpression();
    setState(255);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::EQEQ

    || _la == Grammar::NEQ) {
      setState(251);
      _la = _input->LA(1);
      if (!(_la == Grammar::EQEQ

      || _la == Grammar::NEQ)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(252);
      relationalExpression();
      setState(257);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

Grammar::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::ShiftExpressionContext *> Grammar::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<Grammar::ShiftExpressionContext>();
}

Grammar::ShiftExpressionContext* Grammar::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<Grammar::ShiftExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::RelationalExpressionContext::GT() {
  return getTokens(Grammar::GT);
}

tree::TerminalNode* Grammar::RelationalExpressionContext::GT(size_t i) {
  return getToken(Grammar::GT, i);
}

std::vector<tree::TerminalNode *> Grammar::RelationalExpressionContext::LT() {
  return getTokens(Grammar::LT);
}

tree::TerminalNode* Grammar::RelationalExpressionContext::LT(size_t i) {
  return getToken(Grammar::LT, i);
}

std::vector<tree::TerminalNode *> Grammar::RelationalExpressionContext::GTE() {
  return getTokens(Grammar::GTE);
}

tree::TerminalNode* Grammar::RelationalExpressionContext::GTE(size_t i) {
  return getToken(Grammar::GTE, i);
}

std::vector<tree::TerminalNode *> Grammar::RelationalExpressionContext::LTE() {
  return getTokens(Grammar::LTE);
}

tree::TerminalNode* Grammar::RelationalExpressionContext::LTE(size_t i) {
  return getToken(Grammar::LTE, i);
}


size_t Grammar::RelationalExpressionContext::getRuleIndex() const {
  return Grammar::RuleRelationalExpression;
}

void Grammar::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void Grammar::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


std::any Grammar::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::RelationalExpressionContext* Grammar::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, Grammar::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    shiftExpression();
    setState(263);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 64424509440) != 0)) {
      setState(259);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 64424509440) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(260);
      shiftExpression();
      setState(265);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

Grammar::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::AdditiveExpressionContext *> Grammar::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<Grammar::AdditiveExpressionContext>();
}

Grammar::AdditiveExpressionContext* Grammar::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<Grammar::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::ShiftExpressionContext::SHL() {
  return getTokens(Grammar::SHL);
}

tree::TerminalNode* Grammar::ShiftExpressionContext::SHL(size_t i) {
  return getToken(Grammar::SHL, i);
}

std::vector<tree::TerminalNode *> Grammar::ShiftExpressionContext::SHR() {
  return getTokens(Grammar::SHR);
}

tree::TerminalNode* Grammar::ShiftExpressionContext::SHR(size_t i) {
  return getToken(Grammar::SHR, i);
}


size_t Grammar::ShiftExpressionContext::getRuleIndex() const {
  return Grammar::RuleShiftExpression;
}

void Grammar::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void Grammar::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}


std::any Grammar::ShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ShiftExpressionContext* Grammar::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, Grammar::RuleShiftExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    additiveExpression();
    setState(271);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::SHL

    || _la == Grammar::SHR) {
      setState(267);
      _la = _input->LA(1);
      if (!(_la == Grammar::SHL

      || _la == Grammar::SHR)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(268);
      additiveExpression();
      setState(273);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

Grammar::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::MultiplicativeExpressionContext *> Grammar::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<Grammar::MultiplicativeExpressionContext>();
}

Grammar::MultiplicativeExpressionContext* Grammar::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<Grammar::MultiplicativeExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::AdditiveExpressionContext::PLUS() {
  return getTokens(Grammar::PLUS);
}

tree::TerminalNode* Grammar::AdditiveExpressionContext::PLUS(size_t i) {
  return getToken(Grammar::PLUS, i);
}

std::vector<tree::TerminalNode *> Grammar::AdditiveExpressionContext::MINUS() {
  return getTokens(Grammar::MINUS);
}

tree::TerminalNode* Grammar::AdditiveExpressionContext::MINUS(size_t i) {
  return getToken(Grammar::MINUS, i);
}


size_t Grammar::AdditiveExpressionContext::getRuleIndex() const {
  return Grammar::RuleAdditiveExpression;
}

void Grammar::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void Grammar::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


std::any Grammar::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::AdditiveExpressionContext* Grammar::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, Grammar::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(274);
    multiplicativeExpression();
    setState(279);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(275);
        _la = _input->LA(1);
        if (!(_la == Grammar::PLUS

        || _la == Grammar::MINUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(276);
        multiplicativeExpression(); 
      }
      setState(281);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

Grammar::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::PowerExpressionContext *> Grammar::MultiplicativeExpressionContext::powerExpression() {
  return getRuleContexts<Grammar::PowerExpressionContext>();
}

Grammar::PowerExpressionContext* Grammar::MultiplicativeExpressionContext::powerExpression(size_t i) {
  return getRuleContext<Grammar::PowerExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::MultiplicativeExpressionContext::MUL() {
  return getTokens(Grammar::MUL);
}

tree::TerminalNode* Grammar::MultiplicativeExpressionContext::MUL(size_t i) {
  return getToken(Grammar::MUL, i);
}

std::vector<tree::TerminalNode *> Grammar::MultiplicativeExpressionContext::DIV() {
  return getTokens(Grammar::DIV);
}

tree::TerminalNode* Grammar::MultiplicativeExpressionContext::DIV(size_t i) {
  return getToken(Grammar::DIV, i);
}

std::vector<tree::TerminalNode *> Grammar::MultiplicativeExpressionContext::MOD() {
  return getTokens(Grammar::MOD);
}

tree::TerminalNode* Grammar::MultiplicativeExpressionContext::MOD(size_t i) {
  return getToken(Grammar::MOD, i);
}


size_t Grammar::MultiplicativeExpressionContext::getRuleIndex() const {
  return Grammar::RuleMultiplicativeExpression;
}

void Grammar::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void Grammar::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


std::any Grammar::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::MultiplicativeExpressionContext* Grammar::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, Grammar::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    powerExpression();
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 229376) != 0)) {
      setState(283);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 229376) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(284);
      powerExpression();
      setState(289);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PowerExpressionContext ------------------------------------------------------------------

Grammar::PowerExpressionContext::PowerExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::UnaryExpressionContext* Grammar::PowerExpressionContext::unaryExpression() {
  return getRuleContext<Grammar::UnaryExpressionContext>(0);
}

std::vector<tree::TerminalNode *> Grammar::PowerExpressionContext::MUL() {
  return getTokens(Grammar::MUL);
}

tree::TerminalNode* Grammar::PowerExpressionContext::MUL(size_t i) {
  return getToken(Grammar::MUL, i);
}

Grammar::PowerExpressionContext* Grammar::PowerExpressionContext::powerExpression() {
  return getRuleContext<Grammar::PowerExpressionContext>(0);
}


size_t Grammar::PowerExpressionContext::getRuleIndex() const {
  return Grammar::RulePowerExpression;
}

void Grammar::PowerExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPowerExpression(this);
}

void Grammar::PowerExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPowerExpression(this);
}


std::any Grammar::PowerExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitPowerExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::PowerExpressionContext* Grammar::powerExpression() {
  PowerExpressionContext *_localctx = _tracker.createInstance<PowerExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, Grammar::RulePowerExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    unaryExpression();
    setState(294);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(291);
      match(Grammar::MUL);
      setState(292);
      match(Grammar::MUL);
      setState(293);
      powerExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

Grammar::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::PrimaryExpressionContext* Grammar::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<Grammar::PrimaryExpressionContext>(0);
}

std::vector<tree::TerminalNode *> Grammar::UnaryExpressionContext::NOT() {
  return getTokens(Grammar::NOT);
}

tree::TerminalNode* Grammar::UnaryExpressionContext::NOT(size_t i) {
  return getToken(Grammar::NOT, i);
}

tree::TerminalNode* Grammar::UnaryExpressionContext::BIT_NOT() {
  return getToken(Grammar::BIT_NOT, 0);
}

tree::TerminalNode* Grammar::UnaryExpressionContext::PLUS() {
  return getToken(Grammar::PLUS, 0);
}

tree::TerminalNode* Grammar::UnaryExpressionContext::MINUS() {
  return getToken(Grammar::MINUS, 0);
}


size_t Grammar::UnaryExpressionContext::getRuleIndex() const {
  return Grammar::RuleUnaryExpression;
}

void Grammar::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void Grammar::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}


std::any Grammar::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::UnaryExpressionContext* Grammar::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, Grammar::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(306);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::NOT: {
        setState(296);
        match(Grammar::NOT);
        setState(300);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == Grammar::NOT) {
          setState(297);
          match(Grammar::NOT);
          setState(302);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case Grammar::BIT_NOT: {
        setState(303);
        match(Grammar::BIT_NOT);
        break;
      }

      case Grammar::PLUS: {
        setState(304);
        match(Grammar::PLUS);
        break;
      }

      case Grammar::MINUS: {
        setState(305);
        match(Grammar::MINUS);
        break;
      }

      case Grammar::BOOLEAN:
      case Grammar::IDENTIFIER:
      case Grammar::LPAREN:
      case Grammar::FLOAT:
      case Grammar::INTEGER:
      case Grammar::STRING:
      case Grammar::FORMATTED_STRING_START: {
        break;
      }

    default:
      break;
    }
    setState(308);
    primaryExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

Grammar::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::PrimaryExpressionContext::LPAREN() {
  return getToken(Grammar::LPAREN, 0);
}

Grammar::ExpressionContext* Grammar::PrimaryExpressionContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}

tree::TerminalNode* Grammar::PrimaryExpressionContext::RPAREN() {
  return getToken(Grammar::RPAREN, 0);
}

Grammar::LiteralsContext* Grammar::PrimaryExpressionContext::literals() {
  return getRuleContext<Grammar::LiteralsContext>(0);
}

Grammar::MemberExpressionContext* Grammar::PrimaryExpressionContext::memberExpression() {
  return getRuleContext<Grammar::MemberExpressionContext>(0);
}


size_t Grammar::PrimaryExpressionContext::getRuleIndex() const {
  return Grammar::RulePrimaryExpression;
}

void Grammar::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void Grammar::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


std::any Grammar::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::PrimaryExpressionContext* Grammar::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, Grammar::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(316);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(310);
      match(Grammar::LPAREN);
      setState(311);
      expression();
      setState(312);
      match(Grammar::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(314);
      literals();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(315);
      memberExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralsContext ------------------------------------------------------------------

Grammar::LiteralsContext::LiteralsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::NumberLiteralsContext* Grammar::LiteralsContext::numberLiterals() {
  return getRuleContext<Grammar::NumberLiteralsContext>(0);
}

Grammar::StringLiteralsContext* Grammar::LiteralsContext::stringLiterals() {
  return getRuleContext<Grammar::StringLiteralsContext>(0);
}

Grammar::BooleanLiteralContext* Grammar::LiteralsContext::booleanLiteral() {
  return getRuleContext<Grammar::BooleanLiteralContext>(0);
}

Grammar::IdentifierLiteralContext* Grammar::LiteralsContext::identifierLiteral() {
  return getRuleContext<Grammar::IdentifierLiteralContext>(0);
}


size_t Grammar::LiteralsContext::getRuleIndex() const {
  return Grammar::RuleLiterals;
}

void Grammar::LiteralsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiterals(this);
}

void Grammar::LiteralsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiterals(this);
}


std::any Grammar::LiteralsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitLiterals(this);
  else
    return visitor->visitChildren(this);
}

Grammar::LiteralsContext* Grammar::literals() {
  LiteralsContext *_localctx = _tracker.createInstance<LiteralsContext>(_ctx, getState());
  enterRule(_localctx, 46, Grammar::RuleLiterals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(318);
      numberLiterals();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(319);
      stringLiterals();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(320);
      booleanLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(321);
      identifierLiteral();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberLiteralsContext ------------------------------------------------------------------

Grammar::NumberLiteralsContext::NumberLiteralsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::IntegerLiteralContext* Grammar::NumberLiteralsContext::integerLiteral() {
  return getRuleContext<Grammar::IntegerLiteralContext>(0);
}

Grammar::FloatLiteralContext* Grammar::NumberLiteralsContext::floatLiteral() {
  return getRuleContext<Grammar::FloatLiteralContext>(0);
}


size_t Grammar::NumberLiteralsContext::getRuleIndex() const {
  return Grammar::RuleNumberLiterals;
}

void Grammar::NumberLiteralsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumberLiterals(this);
}

void Grammar::NumberLiteralsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumberLiterals(this);
}


std::any Grammar::NumberLiteralsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitNumberLiterals(this);
  else
    return visitor->visitChildren(this);
}

Grammar::NumberLiteralsContext* Grammar::numberLiterals() {
  NumberLiteralsContext *_localctx = _tracker.createInstance<NumberLiteralsContext>(_ctx, getState());
  enterRule(_localctx, 48, Grammar::RuleNumberLiterals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(326);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(324);
        integerLiteral();
        break;
      }

      case Grammar::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(325);
        floatLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralsContext ------------------------------------------------------------------

Grammar::StringLiteralsContext::StringLiteralsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::StringLiteralContext* Grammar::StringLiteralsContext::stringLiteral() {
  return getRuleContext<Grammar::StringLiteralContext>(0);
}

Grammar::FormattedStringContext* Grammar::StringLiteralsContext::formattedString() {
  return getRuleContext<Grammar::FormattedStringContext>(0);
}

Grammar::IdentifierLiteralContext* Grammar::StringLiteralsContext::identifierLiteral() {
  return getRuleContext<Grammar::IdentifierLiteralContext>(0);
}


size_t Grammar::StringLiteralsContext::getRuleIndex() const {
  return Grammar::RuleStringLiterals;
}

void Grammar::StringLiteralsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLiterals(this);
}

void Grammar::StringLiteralsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLiterals(this);
}


std::any Grammar::StringLiteralsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitStringLiterals(this);
  else
    return visitor->visitChildren(this);
}

Grammar::StringLiteralsContext* Grammar::stringLiterals() {
  StringLiteralsContext *_localctx = _tracker.createInstance<StringLiteralsContext>(_ctx, getState());
  enterRule(_localctx, 50, Grammar::RuleStringLiterals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(331);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(328);
        stringLiteral();
        break;
      }

      case Grammar::FORMATTED_STRING_START: {
        enterOuterAlt(_localctx, 2);
        setState(329);
        formattedString();
        break;
      }

      case Grammar::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(330);
        identifierLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormattedStringContext ------------------------------------------------------------------

Grammar::FormattedStringContext::FormattedStringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::FormattedStringContext::FORMATTED_STRING_START() {
  return getToken(Grammar::FORMATTED_STRING_START, 0);
}

tree::TerminalNode* Grammar::FormattedStringContext::FORMATTED_STRING_END() {
  return getToken(Grammar::FORMATTED_STRING_END, 0);
}

std::vector<Grammar::FormattedStringContentContext *> Grammar::FormattedStringContext::formattedStringContent() {
  return getRuleContexts<Grammar::FormattedStringContentContext>();
}

Grammar::FormattedStringContentContext* Grammar::FormattedStringContext::formattedStringContent(size_t i) {
  return getRuleContext<Grammar::FormattedStringContentContext>(i);
}


size_t Grammar::FormattedStringContext::getRuleIndex() const {
  return Grammar::RuleFormattedString;
}

void Grammar::FormattedStringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormattedString(this);
}

void Grammar::FormattedStringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormattedString(this);
}


std::any Grammar::FormattedStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitFormattedString(this);
  else
    return visitor->visitChildren(this);
}

Grammar::FormattedStringContext* Grammar::formattedString() {
  FormattedStringContext *_localctx = _tracker.createInstance<FormattedStringContext>(_ctx, getState());
  enterRule(_localctx, 52, Grammar::RuleFormattedString);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    match(Grammar::FORMATTED_STRING_START);
    setState(337);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 504403158265495552) != 0)) {
      setState(334);
      formattedStringContent();
      setState(339);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(340);
    match(Grammar::FORMATTED_STRING_END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormattedStringContentContext ------------------------------------------------------------------

Grammar::FormattedStringContentContext::FormattedStringContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::FormattedStringContentContext::REGEX_LITERAL() {
  return getToken(Grammar::REGEX_LITERAL, 0);
}

tree::TerminalNode* Grammar::FormattedStringContentContext::FORMATTED_STRING_TEXT() {
  return getToken(Grammar::FORMATTED_STRING_TEXT, 0);
}

tree::TerminalNode* Grammar::FormattedStringContentContext::LBRACE_IN_FSTRING() {
  return getToken(Grammar::LBRACE_IN_FSTRING, 0);
}

Grammar::ExpressionContext* Grammar::FormattedStringContentContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}

tree::TerminalNode* Grammar::FormattedStringContentContext::RBRACE_IN_FSTRING() {
  return getToken(Grammar::RBRACE_IN_FSTRING, 0);
}


size_t Grammar::FormattedStringContentContext::getRuleIndex() const {
  return Grammar::RuleFormattedStringContent;
}

void Grammar::FormattedStringContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormattedStringContent(this);
}

void Grammar::FormattedStringContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormattedStringContent(this);
}


std::any Grammar::FormattedStringContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitFormattedStringContent(this);
  else
    return visitor->visitChildren(this);
}

Grammar::FormattedStringContentContext* Grammar::formattedStringContent() {
  FormattedStringContentContext *_localctx = _tracker.createInstance<FormattedStringContentContext>(_ctx, getState());
  enterRule(_localctx, 54, Grammar::RuleFormattedStringContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(348);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::REGEX_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(342);
        match(Grammar::REGEX_LITERAL);
        break;
      }

      case Grammar::FORMATTED_STRING_TEXT: {
        enterOuterAlt(_localctx, 2);
        setState(343);
        match(Grammar::FORMATTED_STRING_TEXT);
        break;
      }

      case Grammar::LBRACE_IN_FSTRING: {
        enterOuterAlt(_localctx, 3);
        setState(344);
        match(Grammar::LBRACE_IN_FSTRING);
        setState(345);
        expression();
        setState(346);
        match(Grammar::RBRACE_IN_FSTRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

Grammar::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::StringLiteralContext::STRING() {
  return getToken(Grammar::STRING, 0);
}


size_t Grammar::StringLiteralContext::getRuleIndex() const {
  return Grammar::RuleStringLiteral;
}

void Grammar::StringLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLiteral(this);
}

void Grammar::StringLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLiteral(this);
}


std::any Grammar::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

Grammar::StringLiteralContext* Grammar::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 56, Grammar::RuleStringLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(350);
    match(Grammar::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatLiteralContext ------------------------------------------------------------------

Grammar::FloatLiteralContext::FloatLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::FloatLiteralContext::FLOAT() {
  return getToken(Grammar::FLOAT, 0);
}


size_t Grammar::FloatLiteralContext::getRuleIndex() const {
  return Grammar::RuleFloatLiteral;
}

void Grammar::FloatLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatLiteral(this);
}

void Grammar::FloatLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatLiteral(this);
}


std::any Grammar::FloatLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitFloatLiteral(this);
  else
    return visitor->visitChildren(this);
}

Grammar::FloatLiteralContext* Grammar::floatLiteral() {
  FloatLiteralContext *_localctx = _tracker.createInstance<FloatLiteralContext>(_ctx, getState());
  enterRule(_localctx, 58, Grammar::RuleFloatLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(Grammar::FLOAT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

Grammar::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::IntegerLiteralContext::INTEGER() {
  return getToken(Grammar::INTEGER, 0);
}


size_t Grammar::IntegerLiteralContext::getRuleIndex() const {
  return Grammar::RuleIntegerLiteral;
}

void Grammar::IntegerLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerLiteral(this);
}

void Grammar::IntegerLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerLiteral(this);
}


std::any Grammar::IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

Grammar::IntegerLiteralContext* Grammar::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 60, Grammar::RuleIntegerLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    match(Grammar::INTEGER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanLiteralContext ------------------------------------------------------------------

Grammar::BooleanLiteralContext::BooleanLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::BooleanLiteralContext::BOOLEAN() {
  return getToken(Grammar::BOOLEAN, 0);
}


size_t Grammar::BooleanLiteralContext::getRuleIndex() const {
  return Grammar::RuleBooleanLiteral;
}

void Grammar::BooleanLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanLiteral(this);
}

void Grammar::BooleanLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanLiteral(this);
}


std::any Grammar::BooleanLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitBooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}

Grammar::BooleanLiteralContext* Grammar::booleanLiteral() {
  BooleanLiteralContext *_localctx = _tracker.createInstance<BooleanLiteralContext>(_ctx, getState());
  enterRule(_localctx, 62, Grammar::RuleBooleanLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(356);
    match(Grammar::BOOLEAN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NoneLiteralContext ------------------------------------------------------------------

Grammar::NoneLiteralContext::NoneLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::NoneLiteralContext::NONE() {
  return getToken(Grammar::NONE, 0);
}


size_t Grammar::NoneLiteralContext::getRuleIndex() const {
  return Grammar::RuleNoneLiteral;
}

void Grammar::NoneLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNoneLiteral(this);
}

void Grammar::NoneLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNoneLiteral(this);
}


std::any Grammar::NoneLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitNoneLiteral(this);
  else
    return visitor->visitChildren(this);
}

Grammar::NoneLiteralContext* Grammar::noneLiteral() {
  NoneLiteralContext *_localctx = _tracker.createInstance<NoneLiteralContext>(_ctx, getState());
  enterRule(_localctx, 64, Grammar::RuleNoneLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    match(Grammar::NONE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierLiteralContext ------------------------------------------------------------------

Grammar::IdentifierLiteralContext::IdentifierLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::IdentifierLiteralContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}


size_t Grammar::IdentifierLiteralContext::getRuleIndex() const {
  return Grammar::RuleIdentifierLiteral;
}

void Grammar::IdentifierLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierLiteral(this);
}

void Grammar::IdentifierLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierLiteral(this);
}


std::any Grammar::IdentifierLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIdentifierLiteral(this);
  else
    return visitor->visitChildren(this);
}

Grammar::IdentifierLiteralContext* Grammar::identifierLiteral() {
  IdentifierLiteralContext *_localctx = _tracker.createInstance<IdentifierLiteralContext>(_ctx, getState());
  enterRule(_localctx, 66, Grammar::RuleIdentifierLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360);
    match(Grammar::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemberExpressionContext ------------------------------------------------------------------

Grammar::MemberExpressionContext::MemberExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ValueAtomContext* Grammar::MemberExpressionContext::valueAtom() {
  return getRuleContext<Grammar::ValueAtomContext>(0);
}

std::vector<Grammar::ValuePostfixContext *> Grammar::MemberExpressionContext::valuePostfix() {
  return getRuleContexts<Grammar::ValuePostfixContext>();
}

Grammar::ValuePostfixContext* Grammar::MemberExpressionContext::valuePostfix(size_t i) {
  return getRuleContext<Grammar::ValuePostfixContext>(i);
}


size_t Grammar::MemberExpressionContext::getRuleIndex() const {
  return Grammar::RuleMemberExpression;
}

void Grammar::MemberExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberExpression(this);
}

void Grammar::MemberExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberExpression(this);
}


std::any Grammar::MemberExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitMemberExpression(this);
  else
    return visitor->visitChildren(this);
}

Grammar::MemberExpressionContext* Grammar::memberExpression() {
  MemberExpressionContext *_localctx = _tracker.createInstance<MemberExpressionContext>(_ctx, getState());
  enterRule(_localctx, 68, Grammar::RuleMemberExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(362);
    valueAtom();
    setState(366);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(363);
        valuePostfix(); 
      }
      setState(368);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValuePostfixContext ------------------------------------------------------------------

Grammar::ValuePostfixContext::ValuePostfixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ValuePostfixContext::DOT() {
  return getToken(Grammar::DOT, 0);
}

Grammar::IdentifierLiteralContext* Grammar::ValuePostfixContext::identifierLiteral() {
  return getRuleContext<Grammar::IdentifierLiteralContext>(0);
}

tree::TerminalNode* Grammar::ValuePostfixContext::LPAREN() {
  return getToken(Grammar::LPAREN, 0);
}

tree::TerminalNode* Grammar::ValuePostfixContext::RPAREN() {
  return getToken(Grammar::RPAREN, 0);
}

Grammar::ArgumentListContext* Grammar::ValuePostfixContext::argumentList() {
  return getRuleContext<Grammar::ArgumentListContext>(0);
}


size_t Grammar::ValuePostfixContext::getRuleIndex() const {
  return Grammar::RuleValuePostfix;
}

void Grammar::ValuePostfixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValuePostfix(this);
}

void Grammar::ValuePostfixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValuePostfix(this);
}


std::any Grammar::ValuePostfixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitValuePostfix(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ValuePostfixContext* Grammar::valuePostfix() {
  ValuePostfixContext *_localctx = _tracker.createInstance<ValuePostfixContext>(_ctx, getState());
  enterRule(_localctx, 70, Grammar::RuleValuePostfix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(376);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::DOT: {
        enterOuterAlt(_localctx, 1);
        setState(369);
        match(Grammar::DOT);
        setState(370);
        identifierLiteral();
        break;
      }

      case Grammar::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(371);
        match(Grammar::LPAREN);
        setState(373);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 16890697629071360) != 0)) {
          setState(372);
          argumentList();
        }
        setState(375);
        match(Grammar::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

Grammar::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::ExpressionContext *> Grammar::ArgumentListContext::expression() {
  return getRuleContexts<Grammar::ExpressionContext>();
}

Grammar::ExpressionContext* Grammar::ArgumentListContext::expression(size_t i) {
  return getRuleContext<Grammar::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::ArgumentListContext::COMMA() {
  return getTokens(Grammar::COMMA);
}

tree::TerminalNode* Grammar::ArgumentListContext::COMMA(size_t i) {
  return getToken(Grammar::COMMA, i);
}


size_t Grammar::ArgumentListContext::getRuleIndex() const {
  return Grammar::RuleArgumentList;
}

void Grammar::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void Grammar::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any Grammar::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArgumentListContext* Grammar::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 72, Grammar::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(378);
    expression();
    setState(383);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::COMMA) {
      setState(379);
      match(Grammar::COMMA);
      setState(380);
      expression();
      setState(385);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueAtomContext ------------------------------------------------------------------

Grammar::ValueAtomContext::ValueAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::IdentifierLiteralContext* Grammar::ValueAtomContext::identifierLiteral() {
  return getRuleContext<Grammar::IdentifierLiteralContext>(0);
}

Grammar::StringLiteralContext* Grammar::ValueAtomContext::stringLiteral() {
  return getRuleContext<Grammar::StringLiteralContext>(0);
}

tree::TerminalNode* Grammar::ValueAtomContext::LPAREN() {
  return getToken(Grammar::LPAREN, 0);
}

Grammar::BooleanLiteralContext* Grammar::ValueAtomContext::booleanLiteral() {
  return getRuleContext<Grammar::BooleanLiteralContext>(0);
}

tree::TerminalNode* Grammar::ValueAtomContext::RPAREN() {
  return getToken(Grammar::RPAREN, 0);
}

Grammar::NumberLiteralsContext* Grammar::ValueAtomContext::numberLiterals() {
  return getRuleContext<Grammar::NumberLiteralsContext>(0);
}

Grammar::ExpressionContext* Grammar::ValueAtomContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::ValueAtomContext::getRuleIndex() const {
  return Grammar::RuleValueAtom;
}

void Grammar::ValueAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValueAtom(this);
}

void Grammar::ValueAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValueAtom(this);
}


std::any Grammar::ValueAtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitValueAtom(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ValueAtomContext* Grammar::valueAtom() {
  ValueAtomContext *_localctx = _tracker.createInstance<ValueAtomContext>(_ctx, getState());
  enterRule(_localctx, 74, Grammar::RuleValueAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(400);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(386);
      identifierLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(387);
      stringLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(388);
      match(Grammar::LPAREN);
      setState(389);
      booleanLiteral();
      setState(390);
      match(Grammar::RPAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(392);
      match(Grammar::LPAREN);
      setState(393);
      numberLiterals();
      setState(394);
      match(Grammar::RPAREN);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(396);
      match(Grammar::LPAREN);
      setState(397);
      expression();
      setState(398);
      match(Grammar::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariablesContext ------------------------------------------------------------------

Grammar::VariablesContext::VariablesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::VariableDeclarationContext* Grammar::VariablesContext::variableDeclaration() {
  return getRuleContext<Grammar::VariableDeclarationContext>(0);
}

Grammar::VariableDeclarationWithoutAssignmentContext* Grammar::VariablesContext::variableDeclarationWithoutAssignment() {
  return getRuleContext<Grammar::VariableDeclarationWithoutAssignmentContext>(0);
}

Grammar::VariableReAssignmentContext* Grammar::VariablesContext::variableReAssignment() {
  return getRuleContext<Grammar::VariableReAssignmentContext>(0);
}


size_t Grammar::VariablesContext::getRuleIndex() const {
  return Grammar::RuleVariables;
}

void Grammar::VariablesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariables(this);
}

void Grammar::VariablesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariables(this);
}


std::any Grammar::VariablesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitVariables(this);
  else
    return visitor->visitChildren(this);
}

Grammar::VariablesContext* Grammar::variables() {
  VariablesContext *_localctx = _tracker.createInstance<VariablesContext>(_ctx, getState());
  enterRule(_localctx, 76, Grammar::RuleVariables);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(405);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(402);
      variableDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(403);
      variableDeclarationWithoutAssignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(404);
      variableReAssignment();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

Grammar::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::VariableDataTypeContext* Grammar::VariableDeclarationContext::variableDataType() {
  return getRuleContext<Grammar::VariableDataTypeContext>(0);
}

tree::TerminalNode* Grammar::VariableDeclarationContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}

tree::TerminalNode* Grammar::VariableDeclarationContext::EQ() {
  return getToken(Grammar::EQ, 0);
}

Grammar::ExpressionContext* Grammar::VariableDeclarationContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::VariableDeclarationContext::getRuleIndex() const {
  return Grammar::RuleVariableDeclaration;
}

void Grammar::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void Grammar::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any Grammar::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

Grammar::VariableDeclarationContext* Grammar::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 78, Grammar::RuleVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(407);
    variableDataType();
    setState(408);
    match(Grammar::IDENTIFIER);
    setState(409);
    match(Grammar::EQ);
    inVarMode= true;
    setState(411);
    expression();
    inVarMode = false;
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationWithoutAssignmentContext ------------------------------------------------------------------

Grammar::VariableDeclarationWithoutAssignmentContext::VariableDeclarationWithoutAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::VariableDataTypeContext* Grammar::VariableDeclarationWithoutAssignmentContext::variableDataType() {
  return getRuleContext<Grammar::VariableDataTypeContext>(0);
}

tree::TerminalNode* Grammar::VariableDeclarationWithoutAssignmentContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}


size_t Grammar::VariableDeclarationWithoutAssignmentContext::getRuleIndex() const {
  return Grammar::RuleVariableDeclarationWithoutAssignment;
}

void Grammar::VariableDeclarationWithoutAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarationWithoutAssignment(this);
}

void Grammar::VariableDeclarationWithoutAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarationWithoutAssignment(this);
}


std::any Grammar::VariableDeclarationWithoutAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarationWithoutAssignment(this);
  else
    return visitor->visitChildren(this);
}

Grammar::VariableDeclarationWithoutAssignmentContext* Grammar::variableDeclarationWithoutAssignment() {
  VariableDeclarationWithoutAssignmentContext *_localctx = _tracker.createInstance<VariableDeclarationWithoutAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 80, Grammar::RuleVariableDeclarationWithoutAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    variableDataType();
    setState(415);
    match(Grammar::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableReAssignmentContext ------------------------------------------------------------------

Grammar::VariableReAssignmentContext::VariableReAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::VariableReAssignmentContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}

tree::TerminalNode* Grammar::VariableReAssignmentContext::EQ() {
  return getToken(Grammar::EQ, 0);
}

Grammar::ExpressionContext* Grammar::VariableReAssignmentContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::VariableReAssignmentContext::getRuleIndex() const {
  return Grammar::RuleVariableReAssignment;
}

void Grammar::VariableReAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableReAssignment(this);
}

void Grammar::VariableReAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableReAssignment(this);
}


std::any Grammar::VariableReAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitVariableReAssignment(this);
  else
    return visitor->visitChildren(this);
}

Grammar::VariableReAssignmentContext* Grammar::variableReAssignment() {
  VariableReAssignmentContext *_localctx = _tracker.createInstance<VariableReAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 82, Grammar::RuleVariableReAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(417);
    match(Grammar::IDENTIFIER);
    setState(418);
    match(Grammar::EQ);
    setState(419);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDataTypeContext ------------------------------------------------------------------

Grammar::VariableDataTypeContext::VariableDataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::VariableDataTypeContext::INTEGER_TYPES() {
  return getToken(Grammar::INTEGER_TYPES, 0);
}

tree::TerminalNode* Grammar::VariableDataTypeContext::UNSIGNED_INTEGER_TYPES() {
  return getToken(Grammar::UNSIGNED_INTEGER_TYPES, 0);
}

tree::TerminalNode* Grammar::VariableDataTypeContext::FLOAT_TYPES() {
  return getToken(Grammar::FLOAT_TYPES, 0);
}

tree::TerminalNode* Grammar::VariableDataTypeContext::BOOLEAN_TYPES() {
  return getToken(Grammar::BOOLEAN_TYPES, 0);
}

tree::TerminalNode* Grammar::VariableDataTypeContext::STRING_TYPES() {
  return getToken(Grammar::STRING_TYPES, 0);
}

tree::TerminalNode* Grammar::VariableDataTypeContext::REGEX_TYPE() {
  return getToken(Grammar::REGEX_TYPE, 0);
}


size_t Grammar::VariableDataTypeContext::getRuleIndex() const {
  return Grammar::RuleVariableDataType;
}

void Grammar::VariableDataTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDataType(this);
}

void Grammar::VariableDataTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDataType(this);
}


std::any Grammar::VariableDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitVariableDataType(this);
  else
    return visitor->visitChildren(this);
}

Grammar::VariableDataTypeContext* Grammar::variableDataType() {
  VariableDataTypeContext *_localctx = _tracker.createInstance<VariableDataTypeContext>(_ctx, getState());
  enterRule(_localctx, 84, Grammar::RuleVariableDataType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 250) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArraysContext ------------------------------------------------------------------

Grammar::ArraysContext::ArraysContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ArrayDeclarationContext* Grammar::ArraysContext::arrayDeclaration() {
  return getRuleContext<Grammar::ArrayDeclarationContext>(0);
}

Grammar::ArrayReAssignmentContext* Grammar::ArraysContext::arrayReAssignment() {
  return getRuleContext<Grammar::ArrayReAssignmentContext>(0);
}

Grammar::ArrayAccessContext* Grammar::ArraysContext::arrayAccess() {
  return getRuleContext<Grammar::ArrayAccessContext>(0);
}


size_t Grammar::ArraysContext::getRuleIndex() const {
  return Grammar::RuleArrays;
}

void Grammar::ArraysContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrays(this);
}

void Grammar::ArraysContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrays(this);
}


std::any Grammar::ArraysContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrays(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArraysContext* Grammar::arrays() {
  ArraysContext *_localctx = _tracker.createInstance<ArraysContext>(_ctx, getState());
  enterRule(_localctx, 86, Grammar::RuleArrays);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(426);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(423);
      arrayDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(424);
      arrayReAssignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(425);
      arrayAccess();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayAccessContext ------------------------------------------------------------------

Grammar::ArrayAccessContext::ArrayAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ArrayAccessContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}

tree::TerminalNode* Grammar::ArrayAccessContext::LBRACKET() {
  return getToken(Grammar::LBRACKET, 0);
}

Grammar::ArrayIndexListContext* Grammar::ArrayAccessContext::arrayIndexList() {
  return getRuleContext<Grammar::ArrayIndexListContext>(0);
}

tree::TerminalNode* Grammar::ArrayAccessContext::RBRACKET() {
  return getToken(Grammar::RBRACKET, 0);
}


size_t Grammar::ArrayAccessContext::getRuleIndex() const {
  return Grammar::RuleArrayAccess;
}

void Grammar::ArrayAccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayAccess(this);
}

void Grammar::ArrayAccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayAccess(this);
}


std::any Grammar::ArrayAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayAccess(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayAccessContext* Grammar::arrayAccess() {
  ArrayAccessContext *_localctx = _tracker.createInstance<ArrayAccessContext>(_ctx, getState());
  enterRule(_localctx, 88, Grammar::RuleArrayAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(428);
    match(Grammar::IDENTIFIER);
    setState(429);
    match(Grammar::LBRACKET);
    setState(430);
    arrayIndexList();
    setState(431);
    match(Grammar::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayIndexListContext ------------------------------------------------------------------

Grammar::ArrayIndexListContext::ArrayIndexListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::ExpressionContext *> Grammar::ArrayIndexListContext::expression() {
  return getRuleContexts<Grammar::ExpressionContext>();
}

Grammar::ExpressionContext* Grammar::ArrayIndexListContext::expression(size_t i) {
  return getRuleContext<Grammar::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::ArrayIndexListContext::COMMA() {
  return getTokens(Grammar::COMMA);
}

tree::TerminalNode* Grammar::ArrayIndexListContext::COMMA(size_t i) {
  return getToken(Grammar::COMMA, i);
}


size_t Grammar::ArrayIndexListContext::getRuleIndex() const {
  return Grammar::RuleArrayIndexList;
}

void Grammar::ArrayIndexListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayIndexList(this);
}

void Grammar::ArrayIndexListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayIndexList(this);
}


std::any Grammar::ArrayIndexListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayIndexList(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayIndexListContext* Grammar::arrayIndexList() {
  ArrayIndexListContext *_localctx = _tracker.createInstance<ArrayIndexListContext>(_ctx, getState());
  enterRule(_localctx, 90, Grammar::RuleArrayIndexList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
    expression();
    setState(438);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::COMMA) {
      setState(434);
      match(Grammar::COMMA);
      setState(435);
      expression();
      setState(440);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDeclarationContext ------------------------------------------------------------------

Grammar::ArrayDeclarationContext::ArrayDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ArrayTypeContext* Grammar::ArrayDeclarationContext::arrayType() {
  return getRuleContext<Grammar::ArrayTypeContext>(0);
}

tree::TerminalNode* Grammar::ArrayDeclarationContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}

tree::TerminalNode* Grammar::ArrayDeclarationContext::EQ() {
  return getToken(Grammar::EQ, 0);
}

Grammar::ArrayValuesContext* Grammar::ArrayDeclarationContext::arrayValues() {
  return getRuleContext<Grammar::ArrayValuesContext>(0);
}


size_t Grammar::ArrayDeclarationContext::getRuleIndex() const {
  return Grammar::RuleArrayDeclaration;
}

void Grammar::ArrayDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDeclaration(this);
}

void Grammar::ArrayDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDeclaration(this);
}


std::any Grammar::ArrayDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayDeclaration(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayDeclarationContext* Grammar::arrayDeclaration() {
  ArrayDeclarationContext *_localctx = _tracker.createInstance<ArrayDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 92, Grammar::RuleArrayDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(441);
    arrayType();
    setState(442);
    match(Grammar::IDENTIFIER);
    setState(445);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::EQ) {
      setState(443);
      match(Grammar::EQ);
      setState(444);
      arrayValues();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayValuesContext ------------------------------------------------------------------

Grammar::ArrayValuesContext::ArrayValuesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ArrayItemsWithBracketsContext* Grammar::ArrayValuesContext::arrayItemsWithBrackets() {
  return getRuleContext<Grammar::ArrayItemsWithBracketsContext>(0);
}

std::vector<Grammar::ExpressionContext *> Grammar::ArrayValuesContext::expression() {
  return getRuleContexts<Grammar::ExpressionContext>();
}

Grammar::ExpressionContext* Grammar::ArrayValuesContext::expression(size_t i) {
  return getRuleContext<Grammar::ExpressionContext>(i);
}

Grammar::MemberExpressionContext* Grammar::ArrayValuesContext::memberExpression() {
  return getRuleContext<Grammar::MemberExpressionContext>(0);
}


size_t Grammar::ArrayValuesContext::getRuleIndex() const {
  return Grammar::RuleArrayValues;
}

void Grammar::ArrayValuesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayValues(this);
}

void Grammar::ArrayValuesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayValues(this);
}


std::any Grammar::ArrayValuesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayValues(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayValuesContext* Grammar::arrayValues() {
  ArrayValuesContext *_localctx = _tracker.createInstance<ArrayValuesContext>(_ctx, getState());
  enterRule(_localctx, 94, Grammar::RuleArrayValues);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(455);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(447);
      arrayItemsWithBrackets();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(451);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(448);
          expression(); 
        }
        setState(453);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(454);
      memberExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayItemsWithBracketsContext ------------------------------------------------------------------

Grammar::ArrayItemsWithBracketsContext::ArrayItemsWithBracketsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ArrayItemsWithBracketsContext::LBRACKET() {
  return getToken(Grammar::LBRACKET, 0);
}

tree::TerminalNode* Grammar::ArrayItemsWithBracketsContext::RBRACKET() {
  return getToken(Grammar::RBRACKET, 0);
}

std::vector<Grammar::ArrayItemContext *> Grammar::ArrayItemsWithBracketsContext::arrayItem() {
  return getRuleContexts<Grammar::ArrayItemContext>();
}

Grammar::ArrayItemContext* Grammar::ArrayItemsWithBracketsContext::arrayItem(size_t i) {
  return getRuleContext<Grammar::ArrayItemContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::ArrayItemsWithBracketsContext::COMMA() {
  return getTokens(Grammar::COMMA);
}

tree::TerminalNode* Grammar::ArrayItemsWithBracketsContext::COMMA(size_t i) {
  return getToken(Grammar::COMMA, i);
}


size_t Grammar::ArrayItemsWithBracketsContext::getRuleIndex() const {
  return Grammar::RuleArrayItemsWithBrackets;
}

void Grammar::ArrayItemsWithBracketsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayItemsWithBrackets(this);
}

void Grammar::ArrayItemsWithBracketsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayItemsWithBrackets(this);
}


std::any Grammar::ArrayItemsWithBracketsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayItemsWithBrackets(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayItemsWithBracketsContext* Grammar::arrayItemsWithBrackets() {
  ArrayItemsWithBracketsContext *_localctx = _tracker.createInstance<ArrayItemsWithBracketsContext>(_ctx, getState());
  enterRule(_localctx, 96, Grammar::RuleArrayItemsWithBrackets);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(457);
    match(Grammar::LBRACKET);
    setState(466);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16890697662626816) != 0)) {
      setState(458);
      arrayItem();
      setState(463);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::COMMA) {
        setState(459);
        match(Grammar::COMMA);
        setState(460);
        arrayItem();
        setState(465);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(468);
    match(Grammar::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayItemContext ------------------------------------------------------------------

Grammar::ArrayItemContext::ArrayItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ArrayItemsWithBracketsContext* Grammar::ArrayItemContext::arrayItemsWithBrackets() {
  return getRuleContext<Grammar::ArrayItemsWithBracketsContext>(0);
}

Grammar::ArrayElementContext* Grammar::ArrayItemContext::arrayElement() {
  return getRuleContext<Grammar::ArrayElementContext>(0);
}


size_t Grammar::ArrayItemContext::getRuleIndex() const {
  return Grammar::RuleArrayItem;
}

void Grammar::ArrayItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayItem(this);
}

void Grammar::ArrayItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayItem(this);
}


std::any Grammar::ArrayItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayItem(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayItemContext* Grammar::arrayItem() {
  ArrayItemContext *_localctx = _tracker.createInstance<ArrayItemContext>(_ctx, getState());
  enterRule(_localctx, 98, Grammar::RuleArrayItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(472);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::LBRACKET: {
        enterOuterAlt(_localctx, 1);
        setState(470);
        arrayItemsWithBrackets();
        break;
      }

      case Grammar::NONE:
      case Grammar::BOOLEAN:
      case Grammar::IDENTIFIER:
      case Grammar::PLUS:
      case Grammar::MINUS:
      case Grammar::NOT:
      case Grammar::LPAREN:
      case Grammar::BIT_NOT:
      case Grammar::FLOAT:
      case Grammar::INTEGER:
      case Grammar::STRING:
      case Grammar::FORMATTED_STRING_START: {
        enterOuterAlt(_localctx, 2);
        setState(471);
        arrayElement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayElementContext ------------------------------------------------------------------

Grammar::ArrayElementContext::ArrayElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::StringLiteralContext* Grammar::ArrayElementContext::stringLiteral() {
  return getRuleContext<Grammar::StringLiteralContext>(0);
}

Grammar::FormattedStringContext* Grammar::ArrayElementContext::formattedString() {
  return getRuleContext<Grammar::FormattedStringContext>(0);
}

Grammar::IdentifierLiteralContext* Grammar::ArrayElementContext::identifierLiteral() {
  return getRuleContext<Grammar::IdentifierLiteralContext>(0);
}

Grammar::IntegerLiteralContext* Grammar::ArrayElementContext::integerLiteral() {
  return getRuleContext<Grammar::IntegerLiteralContext>(0);
}

Grammar::FloatLiteralContext* Grammar::ArrayElementContext::floatLiteral() {
  return getRuleContext<Grammar::FloatLiteralContext>(0);
}

Grammar::BooleanLiteralContext* Grammar::ArrayElementContext::booleanLiteral() {
  return getRuleContext<Grammar::BooleanLiteralContext>(0);
}

Grammar::NoneLiteralContext* Grammar::ArrayElementContext::noneLiteral() {
  return getRuleContext<Grammar::NoneLiteralContext>(0);
}

Grammar::ExpressionContext* Grammar::ArrayElementContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::ArrayElementContext::getRuleIndex() const {
  return Grammar::RuleArrayElement;
}

void Grammar::ArrayElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayElement(this);
}

void Grammar::ArrayElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayElement(this);
}


std::any Grammar::ArrayElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayElement(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayElementContext* Grammar::arrayElement() {
  ArrayElementContext *_localctx = _tracker.createInstance<ArrayElementContext>(_ctx, getState());
  enterRule(_localctx, 100, Grammar::RuleArrayElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(482);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(474);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(475);
      formattedString();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(476);
      identifierLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(477);
      integerLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(478);
      floatLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(479);
      booleanLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(480);
      noneLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(481);
      expression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayReAssignmentContext ------------------------------------------------------------------

Grammar::ArrayReAssignmentContext::ArrayReAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ArrayReAssignmentContext::IDENTIFIER() {
  return getToken(Grammar::IDENTIFIER, 0);
}

tree::TerminalNode* Grammar::ArrayReAssignmentContext::EQ() {
  return getToken(Grammar::EQ, 0);
}

Grammar::ArrayItemsWithBracketsContext* Grammar::ArrayReAssignmentContext::arrayItemsWithBrackets() {
  return getRuleContext<Grammar::ArrayItemsWithBracketsContext>(0);
}


size_t Grammar::ArrayReAssignmentContext::getRuleIndex() const {
  return Grammar::RuleArrayReAssignment;
}

void Grammar::ArrayReAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayReAssignment(this);
}

void Grammar::ArrayReAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayReAssignment(this);
}


std::any Grammar::ArrayReAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayReAssignment(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayReAssignmentContext* Grammar::arrayReAssignment() {
  ArrayReAssignmentContext *_localctx = _tracker.createInstance<ArrayReAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 102, Grammar::RuleArrayReAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(484);
    match(Grammar::IDENTIFIER);
    setState(485);
    match(Grammar::EQ);
    setState(486);
    arrayItemsWithBrackets();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

Grammar::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ArrayDataTypeContext* Grammar::ArrayTypeContext::arrayDataType() {
  return getRuleContext<Grammar::ArrayDataTypeContext>(0);
}

tree::TerminalNode* Grammar::ArrayTypeContext::LBRACKET() {
  return getToken(Grammar::LBRACKET, 0);
}

tree::TerminalNode* Grammar::ArrayTypeContext::RBRACKET() {
  return getToken(Grammar::RBRACKET, 0);
}

Grammar::ArrayDeclarationTypeSizesContext* Grammar::ArrayTypeContext::arrayDeclarationTypeSizes() {
  return getRuleContext<Grammar::ArrayDeclarationTypeSizesContext>(0);
}


size_t Grammar::ArrayTypeContext::getRuleIndex() const {
  return Grammar::RuleArrayType;
}

void Grammar::ArrayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayType(this);
}

void Grammar::ArrayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayType(this);
}


std::any Grammar::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayTypeContext* Grammar::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 104, Grammar::RuleArrayType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(488);
    arrayDataType();
    setState(494);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::LBRACKET) {
      setState(489);
      match(Grammar::LBRACKET);
      setState(491);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 16890697629071360) != 0)) {
        setState(490);
        arrayDeclarationTypeSizes();
      }
      setState(493);
      match(Grammar::RBRACKET);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDeclarationTypeSizesContext ------------------------------------------------------------------

Grammar::ArrayDeclarationTypeSizesContext::ArrayDeclarationTypeSizesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Grammar::ExpressionContext *> Grammar::ArrayDeclarationTypeSizesContext::expression() {
  return getRuleContexts<Grammar::ExpressionContext>();
}

Grammar::ExpressionContext* Grammar::ArrayDeclarationTypeSizesContext::expression(size_t i) {
  return getRuleContext<Grammar::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::ArrayDeclarationTypeSizesContext::COMMA() {
  return getTokens(Grammar::COMMA);
}

tree::TerminalNode* Grammar::ArrayDeclarationTypeSizesContext::COMMA(size_t i) {
  return getToken(Grammar::COMMA, i);
}


size_t Grammar::ArrayDeclarationTypeSizesContext::getRuleIndex() const {
  return Grammar::RuleArrayDeclarationTypeSizes;
}

void Grammar::ArrayDeclarationTypeSizesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDeclarationTypeSizes(this);
}

void Grammar::ArrayDeclarationTypeSizesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDeclarationTypeSizes(this);
}


std::any Grammar::ArrayDeclarationTypeSizesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayDeclarationTypeSizes(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayDeclarationTypeSizesContext* Grammar::arrayDeclarationTypeSizes() {
  ArrayDeclarationTypeSizesContext *_localctx = _tracker.createInstance<ArrayDeclarationTypeSizesContext>(_ctx, getState());
  enterRule(_localctx, 106, Grammar::RuleArrayDeclarationTypeSizes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(496);
    expression();
    setState(501);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::COMMA) {
      setState(497);
      match(Grammar::COMMA);
      setState(498);
      expression();
      setState(503);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDataTypeContext ------------------------------------------------------------------

Grammar::ArrayDataTypeContext::ArrayDataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ArrayDataTypeContext::INTEGER_TYPES() {
  return getToken(Grammar::INTEGER_TYPES, 0);
}

tree::TerminalNode* Grammar::ArrayDataTypeContext::UNSIGNED_INTEGER_TYPES() {
  return getToken(Grammar::UNSIGNED_INTEGER_TYPES, 0);
}

tree::TerminalNode* Grammar::ArrayDataTypeContext::FLOAT_TYPES() {
  return getToken(Grammar::FLOAT_TYPES, 0);
}

tree::TerminalNode* Grammar::ArrayDataTypeContext::BOOLEAN_TYPES() {
  return getToken(Grammar::BOOLEAN_TYPES, 0);
}

tree::TerminalNode* Grammar::ArrayDataTypeContext::STRING_TYPES() {
  return getToken(Grammar::STRING_TYPES, 0);
}


size_t Grammar::ArrayDataTypeContext::getRuleIndex() const {
  return Grammar::RuleArrayDataType;
}

void Grammar::ArrayDataTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDataType(this);
}

void Grammar::ArrayDataTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDataType(this);
}


std::any Grammar::ArrayDataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitArrayDataType(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ArrayDataTypeContext* Grammar::arrayDataType() {
  ArrayDataTypeContext *_localctx = _tracker.createInstance<ArrayDataTypeContext>(_ctx, getState());
  enterRule(_localctx, 108, Grammar::RuleArrayDataType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

Grammar::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::IfStatementContext::IF() {
  return getToken(Grammar::IF, 0);
}

tree::TerminalNode* Grammar::IfStatementContext::LPAREN() {
  return getToken(Grammar::LPAREN, 0);
}

Grammar::IfStatementConditionContext* Grammar::IfStatementContext::ifStatementCondition() {
  return getRuleContext<Grammar::IfStatementConditionContext>(0);
}

tree::TerminalNode* Grammar::IfStatementContext::RPAREN() {
  return getToken(Grammar::RPAREN, 0);
}

Grammar::IfStatementBodyContext* Grammar::IfStatementContext::ifStatementBody() {
  return getRuleContext<Grammar::IfStatementBodyContext>(0);
}

std::vector<Grammar::ElseIfStatementContext *> Grammar::IfStatementContext::elseIfStatement() {
  return getRuleContexts<Grammar::ElseIfStatementContext>();
}

Grammar::ElseIfStatementContext* Grammar::IfStatementContext::elseIfStatement(size_t i) {
  return getRuleContext<Grammar::ElseIfStatementContext>(i);
}

Grammar::ElseStatementContext* Grammar::IfStatementContext::elseStatement() {
  return getRuleContext<Grammar::ElseStatementContext>(0);
}


size_t Grammar::IfStatementContext::getRuleIndex() const {
  return Grammar::RuleIfStatement;
}

void Grammar::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void Grammar::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


std::any Grammar::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

Grammar::IfStatementContext* Grammar::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 110, Grammar::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(506);
    match(Grammar::IF);
    setState(507);
    match(Grammar::LPAREN);
    setState(508);
    ifStatementCondition();
    setState(509);
    match(Grammar::RPAREN);
    setState(510);
    ifStatementBody();

    setState(514);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(511);
        elseIfStatement(); 
      }
      setState(516);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    }
    setState(518);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::ELSE) {
      setState(517);
      elseStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseIfStatementContext ------------------------------------------------------------------

Grammar::ElseIfStatementContext::ElseIfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ElseIfStatementContext::ELSE() {
  return getToken(Grammar::ELSE, 0);
}

tree::TerminalNode* Grammar::ElseIfStatementContext::IF() {
  return getToken(Grammar::IF, 0);
}

tree::TerminalNode* Grammar::ElseIfStatementContext::LPAREN() {
  return getToken(Grammar::LPAREN, 0);
}

tree::TerminalNode* Grammar::ElseIfStatementContext::RPAREN() {
  return getToken(Grammar::RPAREN, 0);
}

Grammar::IfStatementBodyContext* Grammar::ElseIfStatementContext::ifStatementBody() {
  return getRuleContext<Grammar::IfStatementBodyContext>(0);
}

Grammar::IfStatementConditionContext* Grammar::ElseIfStatementContext::ifStatementCondition() {
  return getRuleContext<Grammar::IfStatementConditionContext>(0);
}


size_t Grammar::ElseIfStatementContext::getRuleIndex() const {
  return Grammar::RuleElseIfStatement;
}

void Grammar::ElseIfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseIfStatement(this);
}

void Grammar::ElseIfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseIfStatement(this);
}


std::any Grammar::ElseIfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitElseIfStatement(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ElseIfStatementContext* Grammar::elseIfStatement() {
  ElseIfStatementContext *_localctx = _tracker.createInstance<ElseIfStatementContext>(_ctx, getState());
  enterRule(_localctx, 112, Grammar::RuleElseIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(520);
    match(Grammar::ELSE);
    setState(521);
    match(Grammar::IF);
    setState(522);
    match(Grammar::LPAREN);
    setState(524);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16890697629071360) != 0)) {
      setState(523);
      ifStatementCondition();
    }
    setState(526);
    match(Grammar::RPAREN);
    setState(527);
    ifStatementBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementConditionContext ------------------------------------------------------------------

Grammar::IfStatementConditionContext::IfStatementConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ExpressionContext* Grammar::IfStatementConditionContext::expression() {
  return getRuleContext<Grammar::ExpressionContext>(0);
}


size_t Grammar::IfStatementConditionContext::getRuleIndex() const {
  return Grammar::RuleIfStatementCondition;
}

void Grammar::IfStatementConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatementCondition(this);
}

void Grammar::IfStatementConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatementCondition(this);
}


std::any Grammar::IfStatementConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIfStatementCondition(this);
  else
    return visitor->visitChildren(this);
}

Grammar::IfStatementConditionContext* Grammar::ifStatementCondition() {
  IfStatementConditionContext *_localctx = _tracker.createInstance<IfStatementConditionContext>(_ctx, getState());
  enterRule(_localctx, 114, Grammar::RuleIfStatementCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(529);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseStatementContext ------------------------------------------------------------------

Grammar::ElseStatementContext::ElseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ElseStatementContext::ELSE() {
  return getToken(Grammar::ELSE, 0);
}

Grammar::IfStatementBodyContext* Grammar::ElseStatementContext::ifStatementBody() {
  return getRuleContext<Grammar::IfStatementBodyContext>(0);
}


size_t Grammar::ElseStatementContext::getRuleIndex() const {
  return Grammar::RuleElseStatement;
}

void Grammar::ElseStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseStatement(this);
}

void Grammar::ElseStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseStatement(this);
}


std::any Grammar::ElseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitElseStatement(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ElseStatementContext* Grammar::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 116, Grammar::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(531);
    match(Grammar::ELSE);
    setState(532);
    ifStatementBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementBodyContext ------------------------------------------------------------------

Grammar::IfStatementBodyContext::IfStatementBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::IfStatementBodyContext::LBRACE() {
  return getToken(Grammar::LBRACE, 0);
}

tree::TerminalNode* Grammar::IfStatementBodyContext::RBRACE() {
  return getToken(Grammar::RBRACE, 0);
}

std::vector<Grammar::StatementsContext *> Grammar::IfStatementBodyContext::statements() {
  return getRuleContexts<Grammar::StatementsContext>();
}

Grammar::StatementsContext* Grammar::IfStatementBodyContext::statements(size_t i) {
  return getRuleContext<Grammar::StatementsContext>(i);
}


size_t Grammar::IfStatementBodyContext::getRuleIndex() const {
  return Grammar::RuleIfStatementBody;
}

void Grammar::IfStatementBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatementBody(this);
}

void Grammar::IfStatementBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatementBody(this);
}


std::any Grammar::IfStatementBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIfStatementBody(this);
  else
    return visitor->visitChildren(this);
}

Grammar::IfStatementBodyContext* Grammar::ifStatementBody() {
  IfStatementBodyContext *_localctx = _tracker.createInstance<IfStatementBodyContext>(_ctx, getState());
  enterRule(_localctx, 118, Grammar::RuleIfStatementBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(534);
    match(Grammar::LBRACE);
    setState(538);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34905096138554878) != 0)) {
      setState(535);
      statements();
      setState(540);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(541);
    match(Grammar::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

Grammar::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Grammar::ImportStatementWithBracketsContext* Grammar::ImportStatementContext::importStatementWithBrackets() {
  return getRuleContext<Grammar::ImportStatementWithBracketsContext>(0);
}

Grammar::ImportStatementWithoutBracketsContext* Grammar::ImportStatementContext::importStatementWithoutBrackets() {
  return getRuleContext<Grammar::ImportStatementWithoutBracketsContext>(0);
}


size_t Grammar::ImportStatementContext::getRuleIndex() const {
  return Grammar::RuleImportStatement;
}

void Grammar::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void Grammar::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}


std::any Grammar::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ImportStatementContext* Grammar::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 120, Grammar::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(545);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(543);
      importStatementWithBrackets();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(544);
      importStatementWithoutBrackets();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementWithBracketsContext ------------------------------------------------------------------

Grammar::ImportStatementWithBracketsContext::ImportStatementWithBracketsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ImportStatementWithBracketsContext::IMPORT() {
  return getToken(Grammar::IMPORT, 0);
}

tree::TerminalNode* Grammar::ImportStatementWithBracketsContext::LBRACKET() {
  return getToken(Grammar::LBRACKET, 0);
}

tree::TerminalNode* Grammar::ImportStatementWithBracketsContext::RBRACKET() {
  return getToken(Grammar::RBRACKET, 0);
}

tree::TerminalNode* Grammar::ImportStatementWithBracketsContext::FROM() {
  return getToken(Grammar::FROM, 0);
}

Grammar::StringLiteralContext* Grammar::ImportStatementWithBracketsContext::stringLiteral() {
  return getRuleContext<Grammar::StringLiteralContext>(0);
}

std::vector<Grammar::IdentifierLiteralContext *> Grammar::ImportStatementWithBracketsContext::identifierLiteral() {
  return getRuleContexts<Grammar::IdentifierLiteralContext>();
}

Grammar::IdentifierLiteralContext* Grammar::ImportStatementWithBracketsContext::identifierLiteral(size_t i) {
  return getRuleContext<Grammar::IdentifierLiteralContext>(i);
}

std::vector<tree::TerminalNode *> Grammar::ImportStatementWithBracketsContext::COMMA() {
  return getTokens(Grammar::COMMA);
}

tree::TerminalNode* Grammar::ImportStatementWithBracketsContext::COMMA(size_t i) {
  return getToken(Grammar::COMMA, i);
}


size_t Grammar::ImportStatementWithBracketsContext::getRuleIndex() const {
  return Grammar::RuleImportStatementWithBrackets;
}

void Grammar::ImportStatementWithBracketsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatementWithBrackets(this);
}

void Grammar::ImportStatementWithBracketsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatementWithBrackets(this);
}


std::any Grammar::ImportStatementWithBracketsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitImportStatementWithBrackets(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ImportStatementWithBracketsContext* Grammar::importStatementWithBrackets() {
  ImportStatementWithBracketsContext *_localctx = _tracker.createInstance<ImportStatementWithBracketsContext>(_ctx, getState());
  enterRule(_localctx, 122, Grammar::RuleImportStatementWithBrackets);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(547);
    match(Grammar::IMPORT);
    setState(548);
    match(Grammar::LBRACKET);
    setState(557);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::IDENTIFIER) {
      setState(549);
      identifierLiteral();
      setState(554);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::COMMA) {
        setState(550);
        match(Grammar::COMMA);
        setState(551);
        identifierLiteral();
        setState(556);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(559);
    match(Grammar::RBRACKET);
    setState(560);
    match(Grammar::FROM);
    setState(561);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementWithoutBracketsContext ------------------------------------------------------------------

Grammar::ImportStatementWithoutBracketsContext::ImportStatementWithoutBracketsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Grammar::ImportStatementWithoutBracketsContext::IMPORT() {
  return getToken(Grammar::IMPORT, 0);
}

Grammar::IdentifierLiteralContext* Grammar::ImportStatementWithoutBracketsContext::identifierLiteral() {
  return getRuleContext<Grammar::IdentifierLiteralContext>(0);
}

tree::TerminalNode* Grammar::ImportStatementWithoutBracketsContext::FROM() {
  return getToken(Grammar::FROM, 0);
}

Grammar::StringLiteralContext* Grammar::ImportStatementWithoutBracketsContext::stringLiteral() {
  return getRuleContext<Grammar::StringLiteralContext>(0);
}


size_t Grammar::ImportStatementWithoutBracketsContext::getRuleIndex() const {
  return Grammar::RuleImportStatementWithoutBrackets;
}

void Grammar::ImportStatementWithoutBracketsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatementWithoutBrackets(this);
}

void Grammar::ImportStatementWithoutBracketsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatementWithoutBrackets(this);
}


std::any Grammar::ImportStatementWithoutBracketsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitImportStatementWithoutBrackets(this);
  else
    return visitor->visitChildren(this);
}

Grammar::ImportStatementWithoutBracketsContext* Grammar::importStatementWithoutBrackets() {
  ImportStatementWithoutBracketsContext *_localctx = _tracker.createInstance<ImportStatementWithoutBracketsContext>(_ctx, getState());
  enterRule(_localctx, 124, Grammar::RuleImportStatementWithoutBrackets);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(563);
    match(Grammar::IMPORT);
    setState(564);
    identifierLiteral();
    setState(565);
    match(Grammar::FROM);
    setState(566);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void Grammar::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  grammarParserInitialize();
#else
  ::antlr4::internal::call_once(grammarParserOnceFlag, grammarParserInitialize);
#endif
}
