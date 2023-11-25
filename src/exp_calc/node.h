#pragma once
#include <cstddef>
#include <string>
#include <vector>

enum {
  NODE_INT,
  NODE_FLOAT,
  NODE_STRING,
  NODE_OPERATOR,
  NODE_FUNCTION,
  NODE_ERROR
};

struct Node{
  size_t type;
  Node(const size_t type);
  Node* clear();
  void print(size_t indent=0);
};

struct IntNode: public Node{
  int value;
  IntNode(const int value);
}; 

struct FloatNode: public Node{
  float value;
  FloatNode(const float value);
};

struct StringNode: public Node{
  std::string value;
  StringNode(const std::string value);
};

struct OperatorNode: public Node{
  char value;
  Node* left_side;
  Node* right_side;
  OperatorNode(const char value, Node* left_side, Node* right_side);
};

struct FunctionNode: public Node{
  std::string name;
  std::vector<Node*> args;
  FunctionNode(const std::string name, const std::vector<Node*> args);
};

struct ErrorNode: public Node{
  std::string content;
  ErrorNode(const size_t error_type, const std::string content);
};

IntNode* toIntNode(Node* node);
FloatNode* toFloatNode(Node* node);
StringNode* toStringNode(Node* node);
OperatorNode* toOperatorNode(Node* node);
FunctionNode* toFunctionNode(Node* node);
ErrorNode* toErrorNode(Node* node);
