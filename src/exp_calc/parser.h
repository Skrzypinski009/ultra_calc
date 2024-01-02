#pragma once
#include <vector>
#include "lexer.h" // Token
#include "node.h"

class Parser{
  std::vector<Token> tokens;
  size_t idx;
public:
  Node* root_node;
  Parser();
  ~Parser();
  void setTokens(std::vector<Token> tokens);
  void parse();
  void clear();
  Node* popRootNode();

private:
  Token at() const;
  bool eat(size_t token_type);
  bool isEOL();
  
  bool altCondition();
  bool addCondition();
  bool mulCondition();
  Node* parseAlt();
  Node* parseAdd();
  Node* parseMul();
  Node* parseFactor();
};
