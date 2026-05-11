
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
      "program", "statements", "importStatement", "importStatementWithBrackets", 
      "importStatementWithoutBrackets", "literals", "numberLiterals", "stringLiterals", 
      "formattedString", "formattedStringContent", "stringLiteral", "floatLiteral", 
      "integerLiteral", "booleanLiteral", "noneLiteral", "identifierLiteral", 
      "expression", "conditionalExpression", "logicalOrExpression", "logicalAndExpression", 
      "bitwiseOrExpression", "bitwiseXorExpression", "bitwiseAndExpression", 
      "equalityExpression", "relationalExpression", "shiftExpression", "additiveExpression", 
      "multiplicativeExpression", "powerExpression", "unaryExpression", 
      "primaryExpression", "memberExpression", "valuePostfix", "argumentList", 
      "valueAtom", "dictionaryDeclaration", "dictionaryAssignmentBody", 
      "dictionaryDeclarationType", "dictionaryTypeElement", "dictionaryDeclarationTypeArray", 
      "dictionaryDataType", "variables", "variableDeclaration", "variableDeclarationWithoutAssignment", 
      "variableReAssignment", "variableDataType", "arrays", "arrayAccess", 
      "arrayIndexList", "arrayDeclaration", "arrayValues", "arrayItemsWithBrackets", 
      "arrayItem", "arrayElement", "arrayReAssignment", "arrayType", "arrayDeclarationTypeSizes", 
      "arrayDataType", "ifStatement", "elseIfStatement", "ifStatementCondition", 
      "elseStatement", "ifStatementBody"
    },
    std::vector<std::string>{
      "", "'import'", "'from'", "'regex'", "'dict'", "'bool'", "'str'", 
      "", "", "", "'if'", "'else'"
    },
    std::vector<std::string>{
      "", "IMPORT", "FROM", "REGEX_TYPE", "DICT_KEYWORD", "BOOLEAN_TYPES", 
      "STRING_TYPES", "INTEGER_TYPES", "UNSIGNED_INTEGER_TYPES", "FLOAT_TYPES", 
      "IF", "ELSE", "NONE", "BOOLEAN", "IDENTIFIER", "PLUS", "MINUS", "MUL", 
      "DIV", "MOD", "EQ", "EQEQ", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "LBRACKET", "RBRACKET", "DOT", "COMMA", "AMPERSAND", "ANDAND", "OROR", 
      "LT", "LTE", "GT", "GTE", "NEQ", "COLON", "QUESTION", "BIT_OR", "BIT_XOR", 
      "BIT_NOT", "SHL", "SHR", "NEWLINE", "NEWLINE_VISIBLE", "WS_VISIBLE", 
      "COMMENT", "BLOCK_COMMENT", "WS", "FLOAT", "INTEGER", "STRING", "FORMATTED_STRING_START", 
      "FORMATTED_STRING_TEXT", "REGEX_LITERAL", "LBRACE_IN_FSTRING", "FORMATTED_STRING_END", 
      "RBRACE_IN_FSTRING", "EXPR_WS"
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
  	3,1,156,8,1,1,2,1,2,3,2,160,8,2,1,3,1,3,1,3,1,3,1,3,5,3,167,8,3,10,3,
  	12,3,170,9,3,3,3,172,8,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,
  	1,5,1,5,3,5,187,8,5,1,6,1,6,3,6,191,8,6,1,7,1,7,1,7,3,7,196,8,7,1,8,1,
  	8,5,8,200,8,8,10,8,12,8,203,9,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,3,9,213,
  	8,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,
  	1,16,1,17,1,17,1,17,1,17,1,17,1,17,3,17,235,8,17,1,18,1,18,1,18,5,18,
  	240,8,18,10,18,12,18,243,9,18,1,19,1,19,1,19,5,19,248,8,19,10,19,12,19,
  	251,9,19,1,20,1,20,1,20,5,20,256,8,20,10,20,12,20,259,9,20,1,21,1,21,
  	1,21,5,21,264,8,21,10,21,12,21,267,9,21,1,22,1,22,1,22,5,22,272,8,22,
  	10,22,12,22,275,9,22,1,23,1,23,1,23,5,23,280,8,23,10,23,12,23,283,9,23,
  	1,24,1,24,1,24,5,24,288,8,24,10,24,12,24,291,9,24,1,25,1,25,1,25,5,25,
  	296,8,25,10,25,12,25,299,9,25,1,26,1,26,1,26,5,26,304,8,26,10,26,12,26,
  	307,9,26,1,27,1,27,1,27,5,27,312,8,27,10,27,12,27,315,9,27,1,28,1,28,
  	1,28,1,28,3,28,321,8,28,1,29,1,29,5,29,325,8,29,10,29,12,29,328,9,29,
  	1,29,1,29,1,29,3,29,333,8,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,1,30,
  	3,30,343,8,30,1,31,1,31,5,31,347,8,31,10,31,12,31,350,9,31,1,32,1,32,
  	1,32,1,32,3,32,356,8,32,1,32,3,32,359,8,32,1,33,1,33,1,33,5,33,364,8,
  	33,10,33,12,33,367,9,33,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,3,34,383,8,34,1,35,1,35,1,35,1,35,1,35,1,35,
  	1,35,1,35,1,35,1,35,1,35,3,35,396,8,35,5,35,398,8,35,10,35,12,35,401,
  	9,35,3,35,403,8,35,1,35,1,35,1,36,1,36,1,36,1,36,1,37,1,37,1,37,1,37,
  	1,38,1,38,3,38,417,8,38,1,39,1,39,1,39,3,39,422,8,39,1,39,1,39,1,40,1,
  	40,1,41,1,41,1,41,3,41,431,8,41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,
  	43,1,43,1,43,1,44,1,44,1,44,1,44,1,45,1,45,1,46,1,46,1,46,3,46,452,8,
  	46,1,47,1,47,1,47,1,47,1,47,1,48,1,48,1,48,5,48,462,8,48,10,48,12,48,
  	465,9,48,1,49,1,49,1,49,1,49,3,49,471,8,49,1,50,1,50,5,50,475,8,50,10,
  	50,12,50,478,9,50,1,50,3,50,481,8,50,1,51,1,51,1,51,1,51,5,51,487,8,51,
  	10,51,12,51,490,9,51,3,51,492,8,51,1,51,1,51,1,52,1,52,3,52,498,8,52,
  	1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,508,8,53,1,54,1,54,1,54,
  	1,54,1,55,1,55,1,55,3,55,517,8,55,1,55,3,55,520,8,55,1,56,1,56,1,56,5,
  	56,525,8,56,10,56,12,56,528,9,56,1,57,1,57,1,58,1,58,1,58,1,58,1,58,1,
  	58,5,58,538,8,58,10,58,12,58,541,9,58,1,58,3,58,544,8,58,1,59,1,59,1,
  	59,1,59,3,59,550,8,59,1,59,1,59,1,59,1,60,1,60,1,61,1,61,1,61,1,62,1,
  	62,5,62,562,8,62,10,62,12,62,565,9,62,1,62,1,62,1,62,0,0,63,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,
  	102,104,106,108,110,112,114,116,118,120,122,124,0,7,2,0,21,21,38,38,1,
  	0,34,37,1,0,44,45,1,0,15,16,1,0,17,19,1,0,5,9,2,0,3,3,5,9,586,0,129,1,
  	0,0,0,2,155,1,0,0,0,4,159,1,0,0,0,6,161,1,0,0,0,8,177,1,0,0,0,10,186,
  	1,0,0,0,12,190,1,0,0,0,14,195,1,0,0,0,16,197,1,0,0,0,18,212,1,0,0,0,20,
  	214,1,0,0,0,22,216,1,0,0,0,24,218,1,0,0,0,26,220,1,0,0,0,28,222,1,0,0,
  	0,30,224,1,0,0,0,32,226,1,0,0,0,34,228,1,0,0,0,36,236,1,0,0,0,38,244,
  	1,0,0,0,40,252,1,0,0,0,42,260,1,0,0,0,44,268,1,0,0,0,46,276,1,0,0,0,48,
  	284,1,0,0,0,50,292,1,0,0,0,52,300,1,0,0,0,54,308,1,0,0,0,56,316,1,0,0,
  	0,58,332,1,0,0,0,60,342,1,0,0,0,62,344,1,0,0,0,64,358,1,0,0,0,66,360,
  	1,0,0,0,68,382,1,0,0,0,70,384,1,0,0,0,72,406,1,0,0,0,74,410,1,0,0,0,76,
  	416,1,0,0,0,78,418,1,0,0,0,80,425,1,0,0,0,82,430,1,0,0,0,84,432,1,0,0,
  	0,86,439,1,0,0,0,88,442,1,0,0,0,90,446,1,0,0,0,92,451,1,0,0,0,94,453,
  	1,0,0,0,96,458,1,0,0,0,98,466,1,0,0,0,100,480,1,0,0,0,102,482,1,0,0,0,
  	104,497,1,0,0,0,106,507,1,0,0,0,108,509,1,0,0,0,110,513,1,0,0,0,112,521,
  	1,0,0,0,114,529,1,0,0,0,116,531,1,0,0,0,118,545,1,0,0,0,120,554,1,0,0,
  	0,122,556,1,0,0,0,124,559,1,0,0,0,126,128,5,46,0,0,127,126,1,0,0,0,128,
  	131,1,0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,141,1,0,0,0,131,129,1,
  	0,0,0,132,136,3,2,1,0,133,135,5,46,0,0,134,133,1,0,0,0,135,138,1,0,0,
  	0,136,134,1,0,0,0,136,137,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,139,
  	132,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,1,0,0,0,142,144,1,
  	0,0,0,143,141,1,0,0,0,144,145,5,0,0,1,145,1,1,0,0,0,146,156,3,32,16,0,
  	147,156,3,82,41,0,148,156,3,92,46,0,149,156,3,4,2,0,150,156,3,70,35,0,
  	151,156,3,62,31,0,152,156,3,116,58,0,153,156,3,26,13,0,154,156,3,28,14,
  	0,155,146,1,0,0,0,155,147,1,0,0,0,155,148,1,0,0,0,155,149,1,0,0,0,155,
  	150,1,0,0,0,155,151,1,0,0,0,155,152,1,0,0,0,155,153,1,0,0,0,155,154,1,
  	0,0,0,156,3,1,0,0,0,157,160,3,6,3,0,158,160,3,8,4,0,159,157,1,0,0,0,159,
  	158,1,0,0,0,160,5,1,0,0,0,161,162,5,1,0,0,162,171,5,27,0,0,163,168,3,
  	30,15,0,164,165,5,30,0,0,165,167,3,30,15,0,166,164,1,0,0,0,167,170,1,
  	0,0,0,168,166,1,0,0,0,168,169,1,0,0,0,169,172,1,0,0,0,170,168,1,0,0,0,
  	171,163,1,0,0,0,171,172,1,0,0,0,172,173,1,0,0,0,173,174,5,28,0,0,174,
  	175,5,2,0,0,175,176,3,20,10,0,176,7,1,0,0,0,177,178,5,1,0,0,178,179,3,
  	30,15,0,179,180,5,2,0,0,180,181,3,20,10,0,181,9,1,0,0,0,182,187,3,12,
  	6,0,183,187,3,14,7,0,184,187,3,26,13,0,185,187,3,30,15,0,186,182,1,0,
  	0,0,186,183,1,0,0,0,186,184,1,0,0,0,186,185,1,0,0,0,187,11,1,0,0,0,188,
  	191,3,24,12,0,189,191,3,22,11,0,190,188,1,0,0,0,190,189,1,0,0,0,191,13,
  	1,0,0,0,192,196,3,20,10,0,193,196,3,16,8,0,194,196,3,30,15,0,195,192,
  	1,0,0,0,195,193,1,0,0,0,195,194,1,0,0,0,196,15,1,0,0,0,197,201,5,55,0,
  	0,198,200,3,18,9,0,199,198,1,0,0,0,200,203,1,0,0,0,201,199,1,0,0,0,201,
  	202,1,0,0,0,202,204,1,0,0,0,203,201,1,0,0,0,204,205,5,59,0,0,205,17,1,
  	0,0,0,206,213,5,57,0,0,207,213,5,56,0,0,208,209,5,58,0,0,209,210,3,32,
  	16,0,210,211,5,60,0,0,211,213,1,0,0,0,212,206,1,0,0,0,212,207,1,0,0,0,
  	212,208,1,0,0,0,213,19,1,0,0,0,214,215,5,54,0,0,215,21,1,0,0,0,216,217,
  	5,52,0,0,217,23,1,0,0,0,218,219,5,53,0,0,219,25,1,0,0,0,220,221,5,13,
  	0,0,221,27,1,0,0,0,222,223,5,12,0,0,223,29,1,0,0,0,224,225,5,14,0,0,225,
  	31,1,0,0,0,226,227,3,34,17,0,227,33,1,0,0,0,228,234,3,36,18,0,229,230,
  	5,40,0,0,230,231,3,32,16,0,231,232,5,39,0,0,232,233,3,32,16,0,233,235,
  	1,0,0,0,234,229,1,0,0,0,234,235,1,0,0,0,235,35,1,0,0,0,236,241,3,38,19,
  	0,237,238,5,33,0,0,238,240,3,38,19,0,239,237,1,0,0,0,240,243,1,0,0,0,
  	241,239,1,0,0,0,241,242,1,0,0,0,242,37,1,0,0,0,243,241,1,0,0,0,244,249,
  	3,40,20,0,245,246,5,32,0,0,246,248,3,40,20,0,247,245,1,0,0,0,248,251,
  	1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,39,1,0,0,0,251,249,1,0,0,
  	0,252,257,3,42,21,0,253,254,5,41,0,0,254,256,3,42,21,0,255,253,1,0,0,
  	0,256,259,1,0,0,0,257,255,1,0,0,0,257,258,1,0,0,0,258,41,1,0,0,0,259,
  	257,1,0,0,0,260,265,3,44,22,0,261,262,5,42,0,0,262,264,3,44,22,0,263,
  	261,1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,266,1,0,0,0,266,43,1,
  	0,0,0,267,265,1,0,0,0,268,273,3,46,23,0,269,270,5,31,0,0,270,272,3,46,
  	23,0,271,269,1,0,0,0,272,275,1,0,0,0,273,271,1,0,0,0,273,274,1,0,0,0,
  	274,45,1,0,0,0,275,273,1,0,0,0,276,281,3,48,24,0,277,278,7,0,0,0,278,
  	280,3,48,24,0,279,277,1,0,0,0,280,283,1,0,0,0,281,279,1,0,0,0,281,282,
  	1,0,0,0,282,47,1,0,0,0,283,281,1,0,0,0,284,289,3,50,25,0,285,286,7,1,
  	0,0,286,288,3,50,25,0,287,285,1,0,0,0,288,291,1,0,0,0,289,287,1,0,0,0,
  	289,290,1,0,0,0,290,49,1,0,0,0,291,289,1,0,0,0,292,297,3,52,26,0,293,
  	294,7,2,0,0,294,296,3,52,26,0,295,293,1,0,0,0,296,299,1,0,0,0,297,295,
  	1,0,0,0,297,298,1,0,0,0,298,51,1,0,0,0,299,297,1,0,0,0,300,305,3,54,27,
  	0,301,302,7,3,0,0,302,304,3,54,27,0,303,301,1,0,0,0,304,307,1,0,0,0,305,
  	303,1,0,0,0,305,306,1,0,0,0,306,53,1,0,0,0,307,305,1,0,0,0,308,313,3,
  	56,28,0,309,310,7,4,0,0,310,312,3,56,28,0,311,309,1,0,0,0,312,315,1,0,
  	0,0,313,311,1,0,0,0,313,314,1,0,0,0,314,55,1,0,0,0,315,313,1,0,0,0,316,
  	320,3,58,29,0,317,318,5,17,0,0,318,319,5,17,0,0,319,321,3,56,28,0,320,
  	317,1,0,0,0,320,321,1,0,0,0,321,57,1,0,0,0,322,326,5,22,0,0,323,325,5,
  	22,0,0,324,323,1,0,0,0,325,328,1,0,0,0,326,324,1,0,0,0,326,327,1,0,0,
  	0,327,333,1,0,0,0,328,326,1,0,0,0,329,333,5,43,0,0,330,333,5,15,0,0,331,
  	333,5,16,0,0,332,322,1,0,0,0,332,329,1,0,0,0,332,330,1,0,0,0,332,331,
  	1,0,0,0,332,333,1,0,0,0,333,334,1,0,0,0,334,335,3,60,30,0,335,59,1,0,
  	0,0,336,337,5,23,0,0,337,338,3,32,16,0,338,339,5,24,0,0,339,343,1,0,0,
  	0,340,343,3,10,5,0,341,343,3,62,31,0,342,336,1,0,0,0,342,340,1,0,0,0,
  	342,341,1,0,0,0,343,61,1,0,0,0,344,348,3,68,34,0,345,347,3,64,32,0,346,
  	345,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,0,348,349,1,0,0,0,349,63,1,
  	0,0,0,350,348,1,0,0,0,351,352,5,29,0,0,352,359,3,30,15,0,353,355,5,23,
  	0,0,354,356,3,66,33,0,355,354,1,0,0,0,355,356,1,0,0,0,356,357,1,0,0,0,
  	357,359,5,24,0,0,358,351,1,0,0,0,358,353,1,0,0,0,359,65,1,0,0,0,360,365,
  	3,32,16,0,361,362,5,30,0,0,362,364,3,32,16,0,363,361,1,0,0,0,364,367,
  	1,0,0,0,365,363,1,0,0,0,365,366,1,0,0,0,366,67,1,0,0,0,367,365,1,0,0,
  	0,368,383,3,30,15,0,369,383,3,20,10,0,370,371,5,23,0,0,371,372,3,26,13,
  	0,372,373,5,24,0,0,373,383,1,0,0,0,374,375,5,23,0,0,375,376,3,12,6,0,
  	376,377,5,24,0,0,377,383,1,0,0,0,378,379,5,23,0,0,379,380,3,32,16,0,380,
  	381,5,24,0,0,381,383,1,0,0,0,382,368,1,0,0,0,382,369,1,0,0,0,382,370,
  	1,0,0,0,382,374,1,0,0,0,382,378,1,0,0,0,383,69,1,0,0,0,384,385,5,4,0,
  	0,385,386,5,34,0,0,386,387,3,74,37,0,387,388,5,36,0,0,388,389,5,14,0,
  	0,389,390,5,20,0,0,390,402,5,25,0,0,391,399,3,72,36,0,392,393,5,30,0,
  	0,393,395,3,72,36,0,394,396,5,30,0,0,395,394,1,0,0,0,395,396,1,0,0,0,
  	396,398,1,0,0,0,397,392,1,0,0,0,398,401,1,0,0,0,399,397,1,0,0,0,399,400,
  	1,0,0,0,400,403,1,0,0,0,401,399,1,0,0,0,402,391,1,0,0,0,402,403,1,0,0,
  	0,403,404,1,0,0,0,404,405,5,26,0,0,405,71,1,0,0,0,406,407,3,10,5,0,407,
  	408,5,39,0,0,408,409,3,32,16,0,409,73,1,0,0,0,410,411,3,76,38,0,411,412,
  	5,30,0,0,412,413,3,76,38,0,413,75,1,0,0,0,414,417,3,78,39,0,415,417,3,
  	80,40,0,416,414,1,0,0,0,416,415,1,0,0,0,417,77,1,0,0,0,418,419,3,80,40,
  	0,419,421,5,27,0,0,420,422,3,32,16,0,421,420,1,0,0,0,421,422,1,0,0,0,
  	422,423,1,0,0,0,423,424,5,28,0,0,424,79,1,0,0,0,425,426,7,5,0,0,426,81,
  	1,0,0,0,427,431,3,84,42,0,428,431,3,86,43,0,429,431,3,88,44,0,430,427,
  	1,0,0,0,430,428,1,0,0,0,430,429,1,0,0,0,431,83,1,0,0,0,432,433,3,90,45,
  	0,433,434,5,14,0,0,434,435,5,20,0,0,435,436,6,42,-1,0,436,437,3,32,16,
  	0,437,438,6,42,-1,0,438,85,1,0,0,0,439,440,3,90,45,0,440,441,5,14,0,0,
  	441,87,1,0,0,0,442,443,5,14,0,0,443,444,5,20,0,0,444,445,3,32,16,0,445,
  	89,1,0,0,0,446,447,7,6,0,0,447,91,1,0,0,0,448,452,3,98,49,0,449,452,3,
  	108,54,0,450,452,3,94,47,0,451,448,1,0,0,0,451,449,1,0,0,0,451,450,1,
  	0,0,0,452,93,1,0,0,0,453,454,5,14,0,0,454,455,5,27,0,0,455,456,3,96,48,
  	0,456,457,5,28,0,0,457,95,1,0,0,0,458,463,3,32,16,0,459,460,5,30,0,0,
  	460,462,3,32,16,0,461,459,1,0,0,0,462,465,1,0,0,0,463,461,1,0,0,0,463,
  	464,1,0,0,0,464,97,1,0,0,0,465,463,1,0,0,0,466,467,3,110,55,0,467,470,
  	5,14,0,0,468,469,5,20,0,0,469,471,3,100,50,0,470,468,1,0,0,0,470,471,
  	1,0,0,0,471,99,1,0,0,0,472,481,3,102,51,0,473,475,3,32,16,0,474,473,1,
  	0,0,0,475,478,1,0,0,0,476,474,1,0,0,0,476,477,1,0,0,0,477,481,1,0,0,0,
  	478,476,1,0,0,0,479,481,3,62,31,0,480,472,1,0,0,0,480,476,1,0,0,0,480,
  	479,1,0,0,0,481,101,1,0,0,0,482,491,5,27,0,0,483,488,3,104,52,0,484,485,
  	5,30,0,0,485,487,3,104,52,0,486,484,1,0,0,0,487,490,1,0,0,0,488,486,1,
  	0,0,0,488,489,1,0,0,0,489,492,1,0,0,0,490,488,1,0,0,0,491,483,1,0,0,0,
  	491,492,1,0,0,0,492,493,1,0,0,0,493,494,5,28,0,0,494,103,1,0,0,0,495,
  	498,3,102,51,0,496,498,3,106,53,0,497,495,1,0,0,0,497,496,1,0,0,0,498,
  	105,1,0,0,0,499,508,3,20,10,0,500,508,3,16,8,0,501,508,3,30,15,0,502,
  	508,3,24,12,0,503,508,3,22,11,0,504,508,3,26,13,0,505,508,3,28,14,0,506,
  	508,3,32,16,0,507,499,1,0,0,0,507,500,1,0,0,0,507,501,1,0,0,0,507,502,
  	1,0,0,0,507,503,1,0,0,0,507,504,1,0,0,0,507,505,1,0,0,0,507,506,1,0,0,
  	0,508,107,1,0,0,0,509,510,5,14,0,0,510,511,5,20,0,0,511,512,3,102,51,
  	0,512,109,1,0,0,0,513,519,3,114,57,0,514,516,5,27,0,0,515,517,3,112,56,
  	0,516,515,1,0,0,0,516,517,1,0,0,0,517,518,1,0,0,0,518,520,5,28,0,0,519,
  	514,1,0,0,0,519,520,1,0,0,0,520,111,1,0,0,0,521,526,3,32,16,0,522,523,
  	5,30,0,0,523,525,3,32,16,0,524,522,1,0,0,0,525,528,1,0,0,0,526,524,1,
  	0,0,0,526,527,1,0,0,0,527,113,1,0,0,0,528,526,1,0,0,0,529,530,7,5,0,0,
  	530,115,1,0,0,0,531,532,5,10,0,0,532,533,5,23,0,0,533,534,3,120,60,0,
  	534,535,5,24,0,0,535,539,3,124,62,0,536,538,3,118,59,0,537,536,1,0,0,
  	0,538,541,1,0,0,0,539,537,1,0,0,0,539,540,1,0,0,0,540,543,1,0,0,0,541,
  	539,1,0,0,0,542,544,3,122,61,0,543,542,1,0,0,0,543,544,1,0,0,0,544,117,
  	1,0,0,0,545,546,5,11,0,0,546,547,5,10,0,0,547,549,5,23,0,0,548,550,3,
  	120,60,0,549,548,1,0,0,0,549,550,1,0,0,0,550,551,1,0,0,0,551,552,5,24,
  	0,0,552,553,3,124,62,0,553,119,1,0,0,0,554,555,3,32,16,0,555,121,1,0,
  	0,0,556,557,5,11,0,0,557,558,3,124,62,0,558,123,1,0,0,0,559,563,5,25,
  	0,0,560,562,3,2,1,0,561,560,1,0,0,0,562,565,1,0,0,0,563,561,1,0,0,0,563,
  	564,1,0,0,0,564,566,1,0,0,0,565,563,1,0,0,0,566,567,5,26,0,0,567,125,
  	1,0,0,0,54,129,136,141,155,159,168,171,186,190,195,201,212,234,241,249,
  	257,265,273,281,289,297,305,313,320,326,332,342,348,355,358,365,382,395,
  	399,402,416,421,430,451,463,470,476,480,488,491,497,507,516,519,526,539,
  	543,549,563
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
      ((1ULL << _la) & 67562790516291578) != 0)) {
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

Grammar::ImportStatementContext* Grammar::StatementsContext::importStatement() {
  return getRuleContext<Grammar::ImportStatementContext>(0);
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
      importStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(150);
      dictionaryDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(151);
      memberExpression();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(152);
      ifStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(153);
      booleanLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(154);
      noneLiteral();
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
  enterRule(_localctx, 4, Grammar::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(159);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(157);
      importStatementWithBrackets();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(158);
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
  enterRule(_localctx, 6, Grammar::RuleImportStatementWithBrackets);
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
    setState(161);
    match(Grammar::IMPORT);
    setState(162);
    match(Grammar::LBRACKET);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::IDENTIFIER) {
      setState(163);
      identifierLiteral();
      setState(168);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::COMMA) {
        setState(164);
        match(Grammar::COMMA);
        setState(165);
        identifierLiteral();
        setState(170);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(173);
    match(Grammar::RBRACKET);
    setState(174);
    match(Grammar::FROM);
    setState(175);
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
  enterRule(_localctx, 8, Grammar::RuleImportStatementWithoutBrackets);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(Grammar::IMPORT);
    setState(178);
    identifierLiteral();
    setState(179);
    match(Grammar::FROM);
    setState(180);
    stringLiteral();
   
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
  enterRule(_localctx, 10, Grammar::RuleLiterals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(186);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(182);
      numberLiterals();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(183);
      stringLiterals();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(184);
      booleanLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(185);
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
  enterRule(_localctx, 12, Grammar::RuleNumberLiterals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(188);
        integerLiteral();
        break;
      }

      case Grammar::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(189);
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
  enterRule(_localctx, 14, Grammar::RuleStringLiterals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(192);
        stringLiteral();
        break;
      }

      case Grammar::FORMATTED_STRING_START: {
        enterOuterAlt(_localctx, 2);
        setState(193);
        formattedString();
        break;
      }

      case Grammar::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(194);
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
  enterRule(_localctx, 16, Grammar::RuleFormattedString);
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
    setState(197);
    match(Grammar::FORMATTED_STRING_START);
    setState(201);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 504403158265495552) != 0)) {
      setState(198);
      formattedStringContent();
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(204);
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
  enterRule(_localctx, 18, Grammar::RuleFormattedStringContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::REGEX_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(206);
        match(Grammar::REGEX_LITERAL);
        break;
      }

      case Grammar::FORMATTED_STRING_TEXT: {
        enterOuterAlt(_localctx, 2);
        setState(207);
        match(Grammar::FORMATTED_STRING_TEXT);
        break;
      }

      case Grammar::LBRACE_IN_FSTRING: {
        enterOuterAlt(_localctx, 3);
        setState(208);
        match(Grammar::LBRACE_IN_FSTRING);
        setState(209);
        expression();
        setState(210);
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
  enterRule(_localctx, 20, Grammar::RuleStringLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
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
  enterRule(_localctx, 22, Grammar::RuleFloatLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
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
  enterRule(_localctx, 24, Grammar::RuleIntegerLiteral);

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
  enterRule(_localctx, 26, Grammar::RuleBooleanLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
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
  enterRule(_localctx, 28, Grammar::RuleNoneLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
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
  enterRule(_localctx, 30, Grammar::RuleIdentifierLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(224);
    match(Grammar::IDENTIFIER);
   
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
  enterRule(_localctx, 32, Grammar::RuleExpression);

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
  enterRule(_localctx, 34, Grammar::RuleConditionalExpression);
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
    setState(228);
    logicalOrExpression();
    setState(234);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::QUESTION) {
      setState(229);
      match(Grammar::QUESTION);
      setState(230);
      expression();
      setState(231);
      match(Grammar::COLON);
      setState(232);
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
  enterRule(_localctx, 36, Grammar::RuleLogicalOrExpression);
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
    setState(236);
    logicalAndExpression();
    setState(241);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::OROR) {
      setState(237);
      match(Grammar::OROR);
      setState(238);
      logicalAndExpression();
      setState(243);
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
  enterRule(_localctx, 38, Grammar::RuleLogicalAndExpression);
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
    setState(244);
    bitwiseOrExpression();
    setState(249);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::ANDAND) {
      setState(245);
      match(Grammar::ANDAND);
      setState(246);
      bitwiseOrExpression();
      setState(251);
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
  enterRule(_localctx, 40, Grammar::RuleBitwiseOrExpression);
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
    setState(252);
    bitwiseXorExpression();
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::BIT_OR) {
      setState(253);
      match(Grammar::BIT_OR);
      setState(254);
      bitwiseXorExpression();
      setState(259);
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
  enterRule(_localctx, 42, Grammar::RuleBitwiseXorExpression);
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
    setState(260);
    bitwiseAndExpression();
    setState(265);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::BIT_XOR) {
      setState(261);
      match(Grammar::BIT_XOR);
      setState(262);
      bitwiseAndExpression();
      setState(267);
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
  enterRule(_localctx, 44, Grammar::RuleBitwiseAndExpression);
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
    setState(268);
    equalityExpression();
    setState(273);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::AMPERSAND) {
      setState(269);
      match(Grammar::AMPERSAND);
      setState(270);
      equalityExpression();
      setState(275);
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
  enterRule(_localctx, 46, Grammar::RuleEqualityExpression);
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
    setState(276);
    relationalExpression();
    setState(281);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::EQEQ

    || _la == Grammar::NEQ) {
      setState(277);
      _la = _input->LA(1);
      if (!(_la == Grammar::EQEQ

      || _la == Grammar::NEQ)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(278);
      relationalExpression();
      setState(283);
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
  enterRule(_localctx, 48, Grammar::RuleRelationalExpression);
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
    setState(284);
    shiftExpression();
    setState(289);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 257698037760) != 0)) {
      setState(285);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 257698037760) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(286);
      shiftExpression();
      setState(291);
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
  enterRule(_localctx, 50, Grammar::RuleShiftExpression);
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
    setState(292);
    additiveExpression();
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::SHL

    || _la == Grammar::SHR) {
      setState(293);
      _la = _input->LA(1);
      if (!(_la == Grammar::SHL

      || _la == Grammar::SHR)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(294);
      additiveExpression();
      setState(299);
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
  enterRule(_localctx, 52, Grammar::RuleAdditiveExpression);
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
    setState(300);
    multiplicativeExpression();
    setState(305);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(301);
        _la = _input->LA(1);
        if (!(_la == Grammar::PLUS

        || _la == Grammar::MINUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(302);
        multiplicativeExpression(); 
      }
      setState(307);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
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
  enterRule(_localctx, 54, Grammar::RuleMultiplicativeExpression);
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
    setState(308);
    powerExpression();
    setState(313);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 917504) != 0)) {
      setState(309);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 917504) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(310);
      powerExpression();
      setState(315);
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
  enterRule(_localctx, 56, Grammar::RulePowerExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    unaryExpression();
    setState(320);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(317);
      match(Grammar::MUL);
      setState(318);
      match(Grammar::MUL);
      setState(319);
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
  enterRule(_localctx, 58, Grammar::RuleUnaryExpression);
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
    setState(332);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::NOT: {
        setState(322);
        match(Grammar::NOT);
        setState(326);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == Grammar::NOT) {
          setState(323);
          match(Grammar::NOT);
          setState(328);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case Grammar::BIT_NOT: {
        setState(329);
        match(Grammar::BIT_NOT);
        break;
      }

      case Grammar::PLUS: {
        setState(330);
        match(Grammar::PLUS);
        break;
      }

      case Grammar::MINUS: {
        setState(331);
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
    setState(334);
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
  enterRule(_localctx, 60, Grammar::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(342);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(336);
      match(Grammar::LPAREN);
      setState(337);
      expression();
      setState(338);
      match(Grammar::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(340);
      literals();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(341);
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
  enterRule(_localctx, 62, Grammar::RuleMemberExpression);

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
    setState(344);
    valueAtom();
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(345);
        valuePostfix(); 
      }
      setState(350);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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
  enterRule(_localctx, 64, Grammar::RuleValuePostfix);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(358);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::DOT: {
        enterOuterAlt(_localctx, 1);
        setState(351);
        match(Grammar::DOT);
        setState(352);
        identifierLiteral();
        break;
      }

      case Grammar::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(353);
        match(Grammar::LPAREN);
        setState(355);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 67562790516285440) != 0)) {
          setState(354);
          argumentList();
        }
        setState(357);
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
  enterRule(_localctx, 66, Grammar::RuleArgumentList);
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
    setState(360);
    expression();
    setState(365);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::COMMA) {
      setState(361);
      match(Grammar::COMMA);
      setState(362);
      expression();
      setState(367);
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
  enterRule(_localctx, 68, Grammar::RuleValueAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(382);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(368);
      identifierLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(369);
      stringLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(370);
      match(Grammar::LPAREN);
      setState(371);
      booleanLiteral();
      setState(372);
      match(Grammar::RPAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(374);
      match(Grammar::LPAREN);
      setState(375);
      numberLiterals();
      setState(376);
      match(Grammar::RPAREN);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(378);
      match(Grammar::LPAREN);
      setState(379);
      expression();
      setState(380);
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
  enterRule(_localctx, 70, Grammar::RuleDictionaryDeclaration);
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
    setState(384);
    match(Grammar::DICT_KEYWORD);
    setState(385);
    match(Grammar::LT);
    setState(386);
    dictionaryDeclarationType();
    setState(387);
    match(Grammar::GT);
    setState(388);
    match(Grammar::IDENTIFIER);
    setState(389);
    match(Grammar::EQ);
    setState(390);
    match(Grammar::LBRACE);
    setState(402);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67553994410582016) != 0)) {
      setState(391);
      dictionaryAssignmentBody();
      setState(399);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::COMMA) {
        setState(392);
        match(Grammar::COMMA);
        setState(393);
        dictionaryAssignmentBody();
        setState(395);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          setState(394);
          match(Grammar::COMMA);
          break;
        }

        default:
          break;
        }
        setState(401);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(404);
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
  enterRule(_localctx, 72, Grammar::RuleDictionaryAssignmentBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(406);
    literals();
    setState(407);
    match(Grammar::COLON);
    setState(408);
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
  enterRule(_localctx, 74, Grammar::RuleDictionaryDeclarationType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(410);
    dictionaryTypeElement();
    setState(411);
    match(Grammar::COMMA);
    setState(412);
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
  enterRule(_localctx, 76, Grammar::RuleDictionaryTypeElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(416);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(414);
      dictionaryDeclarationTypeArray();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(415);
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
  enterRule(_localctx, 78, Grammar::RuleDictionaryDeclarationTypeArray);
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
    setState(418);
    dictionaryDataType();
    setState(419);
    match(Grammar::LBRACKET);
    setState(421);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67562790516285440) != 0)) {
      setState(420);
      expression();
    }
    setState(423);
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
  enterRule(_localctx, 80, Grammar::RuleDictionaryDataType);
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
    setState(425);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 992) != 0))) {
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
  enterRule(_localctx, 82, Grammar::RuleVariables);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(430);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(427);
      variableDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(428);
      variableDeclarationWithoutAssignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(429);
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
  enterRule(_localctx, 84, Grammar::RuleVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(432);
    variableDataType();
    setState(433);
    match(Grammar::IDENTIFIER);
    setState(434);
    match(Grammar::EQ);
    inVarMode= true;
    setState(436);
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
  enterRule(_localctx, 86, Grammar::RuleVariableDeclarationWithoutAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(439);
    variableDataType();
    setState(440);
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
  enterRule(_localctx, 88, Grammar::RuleVariableReAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(442);
    match(Grammar::IDENTIFIER);
    setState(443);
    match(Grammar::EQ);
    setState(444);
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
  enterRule(_localctx, 90, Grammar::RuleVariableDataType);
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
    setState(446);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1000) != 0))) {
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
  enterRule(_localctx, 92, Grammar::RuleArrays);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(451);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(448);
      arrayDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(449);
      arrayReAssignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(450);
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
  enterRule(_localctx, 94, Grammar::RuleArrayAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
    match(Grammar::IDENTIFIER);
    setState(454);
    match(Grammar::LBRACKET);
    setState(455);
    arrayIndexList();
    setState(456);
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
  enterRule(_localctx, 96, Grammar::RuleArrayIndexList);
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
    setState(458);
    expression();
    setState(463);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::COMMA) {
      setState(459);
      match(Grammar::COMMA);
      setState(460);
      expression();
      setState(465);
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
  enterRule(_localctx, 98, Grammar::RuleArrayDeclaration);
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
    setState(466);
    arrayType();
    setState(467);
    match(Grammar::IDENTIFIER);
    setState(470);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::EQ) {
      setState(468);
      match(Grammar::EQ);
      setState(469);
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
  enterRule(_localctx, 100, Grammar::RuleArrayValues);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(480);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(472);
      arrayItemsWithBrackets();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(476);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(473);
          expression(); 
        }
        setState(478);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(479);
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
  enterRule(_localctx, 102, Grammar::RuleArrayItemsWithBrackets);
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
    setState(482);
    match(Grammar::LBRACKET);
    setState(491);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67562790650507264) != 0)) {
      setState(483);
      arrayItem();
      setState(488);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Grammar::COMMA) {
        setState(484);
        match(Grammar::COMMA);
        setState(485);
        arrayItem();
        setState(490);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(493);
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
  enterRule(_localctx, 104, Grammar::RuleArrayItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(497);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Grammar::LBRACKET: {
        enterOuterAlt(_localctx, 1);
        setState(495);
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
        setState(496);
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
  enterRule(_localctx, 106, Grammar::RuleArrayElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(507);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(499);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(500);
      formattedString();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(501);
      identifierLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(502);
      integerLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(503);
      floatLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(504);
      booleanLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(505);
      noneLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(506);
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
  enterRule(_localctx, 108, Grammar::RuleArrayReAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(509);
    match(Grammar::IDENTIFIER);
    setState(510);
    match(Grammar::EQ);
    setState(511);
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
  enterRule(_localctx, 110, Grammar::RuleArrayType);
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
    setState(513);
    arrayDataType();
    setState(519);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::LBRACKET) {
      setState(514);
      match(Grammar::LBRACKET);
      setState(516);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 67562790516285440) != 0)) {
        setState(515);
        arrayDeclarationTypeSizes();
      }
      setState(518);
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
  enterRule(_localctx, 112, Grammar::RuleArrayDeclarationTypeSizes);
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
    setState(521);
    expression();
    setState(526);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Grammar::COMMA) {
      setState(522);
      match(Grammar::COMMA);
      setState(523);
      expression();
      setState(528);
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
  enterRule(_localctx, 114, Grammar::RuleArrayDataType);
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
    setState(529);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 992) != 0))) {
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
  enterRule(_localctx, 116, Grammar::RuleIfStatement);
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
    setState(531);
    match(Grammar::IF);
    setState(532);
    match(Grammar::LPAREN);
    setState(533);
    ifStatementCondition();
    setState(534);
    match(Grammar::RPAREN);
    setState(535);
    ifStatementBody();

    setState(539);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(536);
        elseIfStatement(); 
      }
      setState(541);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    }
    setState(543);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Grammar::ELSE) {
      setState(542);
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
  enterRule(_localctx, 118, Grammar::RuleElseIfStatement);
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
    setState(545);
    match(Grammar::ELSE);
    setState(546);
    match(Grammar::IF);
    setState(547);
    match(Grammar::LPAREN);
    setState(549);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67562790516285440) != 0)) {
      setState(548);
      ifStatementCondition();
    }
    setState(551);
    match(Grammar::RPAREN);
    setState(552);
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
  enterRule(_localctx, 120, Grammar::RuleIfStatementCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(554);
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
  enterRule(_localctx, 122, Grammar::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(556);
    match(Grammar::ELSE);
    setState(557);
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
  enterRule(_localctx, 124, Grammar::RuleIfStatementBody);
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
    setState(559);
    match(Grammar::LBRACE);
    setState(563);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67562790516291578) != 0)) {
      setState(560);
      statements();
      setState(565);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(566);
    match(Grammar::RBRACE);
   
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
