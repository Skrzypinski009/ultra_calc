#pragma once
#include "node.h"
#include <string>
#include <vector>
#include "../workspace/table.h"

class Interpreter{
  std::vector<Table*>* tables;
public:
  Interpreter(std::vector<Table*>* tables);
  ~Interpreter();
  Node* interpret(Node* node_tree);
  void interpretTables();
  void interpretTable(Table*);
  void interpretCell(Table* table, const size_t w, const size_t h);
private:
  Node* interpretNode(Node* node, const size_t table_id, const size_t w, const size_t h);
  Node* interpretOperator(OperatorNode* op_node);
};
