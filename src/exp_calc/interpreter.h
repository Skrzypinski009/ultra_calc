#pragma once
#include "node.h"
#include <string>

class Interpreter{
public:
  Node* interpret(Node* node_tree);
private:
  Node* interpretNode(Node* node);
  Node* interpretOperator(OperatorNode* op_node);
};
