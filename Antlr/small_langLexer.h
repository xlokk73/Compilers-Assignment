
// Generated from small_lang.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  small_langLexer : public antlr4::Lexer {
public:
  enum {
    Program = 1, Block = 2, Statement = 3, FuncDecl = 4, FormalParams = 5, 
    FormalParam = 6, WhileStatement = 7, ForStatement = 8, IfStatement = 9, 
    RtrnStatement = 10, PrintStatement = 11, VariableDecl = 12, Assignment = 13, 
    Expression = 14, SimpleExpression = 15, Term = 16, Factor = 17, Unary = 18, 
    SubExpression = 19, FunctionCall = 20, ActualParams = 21, RelationalOp = 22, 
    AdditiveOp = 23, MultiplicativeOp = 24, Identifier = 25, Literal = 26, 
    FloatLiteral = 27, IntegerLiteral = 28, BooleanLiteral = 29, Auto = 30, 
    Type = 31, Digit = 32, Letter = 33
  };

  small_langLexer(antlr4::CharStream *input);
  ~small_langLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

