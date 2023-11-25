#include "node.h"

#include <iostream>
#include <iomanip>

Node::Node(const size_t type){
  this->type = type;
}

Node* Node::clear(){
  switch(this->type){
    case NODE_INT:
    case NODE_FLOAT:
    case NODE_STRING:
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

void Node::print(size_t indent){
  std::cout<<"{\n" << std::setw(indent*4) << "" << "type: " << this->type << "\n";
  switch(this->type){
    case NODE_INT:
      std::cout << std::setw(indent*4) << "" << " value: " << ((IntNode*)this)->value << "\n"
        << std::setw(indent*4) << "" << "}" << "\n";
      break;
    case NODE_FLOAT:
      std::cout << std::setw(indent*4) << "" << " value: " << ((FloatNode*)this)->value << "\n"
        << std::setw(indent*4) << "" << "}" << "\n";
      break;
    case NODE_STRING:
      std::cout << std::setw(indent*4) << "" << " value: " << ((StringNode*)this)->value << "\n"
        << std::setw(indent*4) << "" << "}" << "\n";
      break;
    case NODE_OPERATOR:
      std::cout << std::setw(indent*4) << "" << "value: " << ((OperatorNode*)this)->value << "\n";
      std::cout << std::setw(indent*4) << "" << "left_side: ";
      ((OperatorNode*)this)->left_side->print(indent+1);
      std::cout << std::setw(indent*4) << "" << "right_side: ";
      ((OperatorNode*)this)->right_side->print(indent+1);
      std::cout << std::setw(indent*4) << "" << "}\n";
      break;
    case NODE_FUNCTION:
      std::cout << std::setw(indent*4) << "" << "name: " << ((FunctionNode*)this)->name << std::endl;
      for(Node* arg : ((FunctionNode*)this)->args){
        std::cout << std::setw(indent*4) << "" << "arg: \n";
        arg->print(indent+1);
      }
      std::cout << std::setw(indent*4) << "" << "}\n";
      break;
  }
}

IntNode::IntNode(const int value): Node(NODE_INT){
  this->value = value;
}

FloatNode::FloatNode(const float value): Node(NODE_FLOAT){
  this->value = value;
}

StringNode::StringNode(const std::string value): Node(NODE_STRING){
  this->value = value;
}

OperatorNode::OperatorNode(const char value, Node* left_side, Node* right_side): Node(NODE_OPERATOR){
  this->value = value;
  this->left_side = left_side;
  this->right_side = right_side;
}

FunctionNode::FunctionNode(const std::string name, const std::vector<Node*> args): Node(NODE_FUNCTION){
  this->name = name;
  for(Node* arg : args){
    this->args.push_back(arg);
  }
}

ErrorNode::ErrorNode(const size_t error_type, const std::string content) : Node(NODE_ERROR){
  this->error_type = error_type;
  this->content = content;
}


IntNode* toIntNode(Node* node){
  if(node->type == NODE_INT)
    return (IntNode*)node;
  else if(node->type == NODE_FLOAT){
    int value = ((FloatNode*)node)->value;
    delete node;
    return new IntNode(value);
  }
  return nullptr;
}

FloatNode* toFloatNode(Node* node){
  if(node->type == NODE_FLOAT)
    return (FloatNode*)node;
  else if(node->type == NODE_INT){
    float value = ((IntNode*)node)->value;
    delete node;
    return new FloatNode(value);
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
