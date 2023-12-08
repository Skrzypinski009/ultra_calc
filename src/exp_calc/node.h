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
  size_t col;
  size_t length;
  Node(const size_t type, const size_t col, const size_t length);
  Node* clear();
  void print(size_t indent=0);
  static std::string toString(const size_t type);
};

struct IntNode: public Node{
  int value;
  IntNode(const size_t col, const int value);
  IntNode(const size_t col, const size_t length, const int value);
}; 

struct FloatNode: public Node{
  float value;
  FloatNode(const size_t col, const float value);
  FloatNode(const size_t col, const size_t length, const float value);
};

struct StringNode: public Node{
  std::string value;
  StringNode(const size_t col, const std::string value);
  StringNode(const size_t col, const size_t length, const std::string value);
};

struct OperatorNode: public Node{
  char value;
  Node* left_side;
  Node* right_side;
  OperatorNode(const size_t col,const char value, Node* left_side, Node* right_side);
};

struct FunctionNode: public Node{
  std::string name;
  std::vector<Node*> args;
  FunctionNode(const size_t col, const size_t length, const std::string name, const std::vector<Node*> args);
};

struct ErrorNode: public Node{
  std::string content;
  ErrorNode(const size_t col, const size_t length, const std::string content);
};

IntNode* toIntNode(Node* node);
FloatNode* toFloatNode(Node* node);
StringNode* toStringNode(Node* node);
OperatorNode* toOperatorNode(Node* node);
FunctionNode* toFunctionNode(Node* node);
ErrorNode* toErrorNode(Node* node);
