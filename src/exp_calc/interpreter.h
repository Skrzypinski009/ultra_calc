#pragma once
#include "node.h"
#include <string>

class Interpreter{
  Node* node_tree;
  std::string error_message;
public:
  Interpreter();
  Interpreter(Node* node_tree);
  Node* interpret();
private:
  Node* interpretNode(Node* node);
  Node* interpretOperator(OperatorNode* op_node);
};
