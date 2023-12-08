#include "node.h"

#include <iostream>
#include <iomanip>

Node::Node(const size_t type, const size_t col, const size_t length){
  this->type = type;
  this->col = col;
  this->length = length;
}

Node* Node::clear(){
  switch(this->type){
    case NODE_INT:
    case NODE_FLOAT:
    case NODE_STRING:
    case NODE_ERROR:
      delete this;
      break;
    case NODE_OPERATOR:
      ((OperatorNode*)this)->left_side->clear();
      ((OperatorNode*)this)->right_side->clear();
      delete this;
      break;
    case NODE_FUNCTION:
      for(Node* arg : ((FunctionNode*)this)->args)
        arg->clear();
      delete this;
      break;
  }
  return nullptr;
}

void printIndent(size_t indent){
  std::cout<<std::setw(indent*4)<<"";
}

void Node::print(size_t indent){
  std::cout <<"{\n";
  printIndent(indent+1);
  std::cout << "type: " << Node::toString(this->type) << "\n";
  printIndent(indent+1);
  std::cout << "col: " << this->col << "\n";
  switch(this->type){
    case NODE_INT:
      printIndent(indent+1);
      std::cout << "value: " << toIntNode(this)->value << "\n";
      break;
    case NODE_FLOAT:
      printIndent(indent+1);
      std::cout << "value: " << toFloatNode(this)->value << "\n";
      break;
    case NODE_STRING:
      printIndent(indent+1);
      std::cout << "value: " << toStringNode(this)->value << "\n";
      break;
    case NODE_OPERATOR:
      printIndent(indent+1);
      std::cout << "value: " << toOperatorNode(this)->value << "\n";
      printIndent(indent+1);
      std::cout << "left_side: ";
      toOperatorNode(this)->left_side->print(indent+1);
      printIndent(indent+1);
      std::cout << "right_side: ";
      toOperatorNode(this)->right_side->print(indent+1);
      break;
    case NODE_FUNCTION:
      printIndent(indent+1);
      std::cout << "name: " << toFunctionNode(this)->name << std::endl;
      for(Node* arg : toFunctionNode(this)->args){
        printIndent(indent+1);
        std::cout << "arg: \n";
        arg->print(indent+1);
      }
      break;
    case NODE_ERROR:
      printIndent(indent+1);
      std::cout << "content: " << toErrorNode(this)->content <<std::endl;
      printIndent(indent+1);
      std::cout << "length: " << toErrorNode(this)->length<<std::endl;
      break;
  }
  printIndent(indent);
  std::cout << "}\n";
}

std::string Node::toString(const size_t type){
  switch(type){
    case NODE_INT:
      return "Int";
    case NODE_FLOAT:
      return "Float";
    case NODE_STRING:
      return "String";
    case NODE_OPERATOR:
      return "Operator";
    case NODE_FUNCTION:
      return "Function";
    case NODE_ERROR:
      return "ERROR";
  }
  return "wrong_type";
}

IntNode::IntNode(const size_t col, const int value): Node(NODE_INT, col, std::to_string(value).length()){
  this->value = value;
}

IntNode::IntNode(const size_t col, const size_t length, const int value): Node(NODE_INT, col, length){
  this->value = value;
}

FloatNode::FloatNode(const size_t col, const float value): Node(NODE_FLOAT, col, std::to_string(value).length()){
  this->value = value;
}

FloatNode::FloatNode(const size_t col, const size_t length, const float value): Node(NODE_FLOAT, col, length){
  this->value = value;
}

StringNode::StringNode(const size_t col, const std::string value): Node(NODE_STRING, col, value.length()+2){
  this->value = value;
}

StringNode::StringNode(const size_t col, const size_t length, const std::string value): Node(NODE_STRING, col, length){
  this->value = value;
}

OperatorNode::OperatorNode(const size_t col, const char value, Node* left_side, Node* right_side): Node(NODE_OPERATOR, col, 1){
  this->value = value;
  this->left_side = left_side;
  this->right_side = right_side;
}

FunctionNode::FunctionNode(const size_t col, const size_t length, const std::string name, const std::vector<Node*> args): Node(NODE_FUNCTION, col, length){
  this->name = name;
  for(Node* arg : args){
    this->args.push_back(arg);
  }
}

ErrorNode::ErrorNode(const size_t col, const size_t length, const std::string content) : Node(NODE_ERROR, col, length){
  this->content = content;
}


IntNode* toIntNode(Node* node){
  if(node->type == NODE_INT)
    return (IntNode*)node;
  else if(node->type == NODE_FLOAT){
    int value = ((FloatNode*)node)->value;
    delete node;
    return new IntNode(node->col, value);
  }
  return nullptr;
}

FloatNode* toFloatNode(Node* node){
  if(node->type == NODE_FLOAT)
    return (FloatNode*)node;
  else if(node->type == NODE_INT){
    float value = ((IntNode*)node)->value;
    delete node;
    return new FloatNode(node->col, value);
  }
  return nullptr;
}

StringNode* toStringNode(Node* node){
  if(node->type == NODE_STRING)
    return (StringNode*)node;
  return nullptr;
}

OperatorNode* toOperatorNode(Node* node){
  if(node->type == NODE_OPERATOR)
    return (OperatorNode*)node;
  return nullptr;
}

FunctionNode* toFunctionNode(Node* node){
  if(node->type == NODE_FUNCTION)
    return (FunctionNode*)node;
  return nullptr;
}

ErrorNode* toErrorNode(Node* node){
  if(node->type == NODE_ERROR){
    return (ErrorNode*)node;
  }
  return nullptr;
}
