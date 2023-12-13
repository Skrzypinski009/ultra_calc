#pragma once
#include "../exp_calc/node.h"
class Cell;
#include "table.h"
#include <string>

class Cell{
  std::string raw_text; // text parsed by user
  Table* parent;
  Node* result_node;    // result node after interpretation
  Node* parsed_exp;     // parsed expression from raw text
public:
  Cell();
  Cell(Table* parent, const std::string raw_text);
  ~Cell();

  void setRawText(const std::string raw_text);
  std::string getRawText() const;

  void setParsedExpression(Node* parsed_exp);
  Node* getParsedExpression() const;

  void setResultNode(Node* result_node);
  Node* getResultNode() const;

  void clear();
  std::string getResultString();
};



