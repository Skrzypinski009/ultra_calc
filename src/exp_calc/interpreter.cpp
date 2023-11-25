#include "interpreter.h"
#include "../utils/utils.h"
#include "node.h"
#include <string>
#include <iostream>

Interpreter::Interpreter(){
  this->node_tree = nullptr;
}

Interpreter::Interpreter(Node* node_tree){
  this->node_tree = node_tree; 
}

Node* Interpreter::interpret(){
  if(this->node_tree){
    return interpretNode(this->node_tree);
  }
  return new IntNode(0);
}

Node* Interpreter::interpretNode(Node* node){
  if(node->type == NODE_INT || node->type == NODE_FLOAT || node->type == NODE_STRING){
    return node;
  } 
  else if(node->type == NODE_OPERATOR){
    OperatorNode* op = (OperatorNode*)node;
    op->left_side = this->interpretNode(op->left_side);
    op->right_side = this->interpretNode(op->right_side);
    Node* result = this->interpretOperator(op);
    op->clear();
    return result;
  }
  else if(node->type == NODE_FUNCTION){
    FunctionNode* func = toFunctionNode(node);
    std::vector<Node*> r_args;
    for(Node* arg: func->args){
      r_args.push_back(interpretNode(arg));
    }
  }
  return nullptr;
}

float calc_floats(float val1, float val2, char op){
  switch(op){
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/':
      if(val2 == 0) return 0;
      return val1/val2;
  }
  return 0;
}

int calc_ints(int val1, int val2, char op){
  switch(op){
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
  }
  return 0;
}

Node* Interpreter::interpretOperator(OperatorNode* op_node){
  Node* left = op_node->left_side;
  Node* right= op_node->right_side;
  if(left->type == NODE_INT || left->type == NODE_FLOAT && right->type == NODE_FLOAT || right->type == NODE_INT){
    if(left->type == NODE_INT && right->type == NODE_INT){
      IntNode* ileft = toIntNode(left);
      IntNode* iright = toIntNode(right);
      if(op_node->value == '/'){
        if(iright==0){
          return new IntNode(0);
        }
        float result = ileft->value/(float)(iright->value);
        return new FloatNode(result);
      }
      int result = calc_ints(ileft->value, iright->value, op_node->value);
      return new IntNode(result);
    }
    else{
      float result = 0;
      // std::cout<<left->type<<", "<<right->type<<std::endl;
      if(left->type == NODE_FLOAT && right->type == NODE_FLOAT) {
        FloatNode* fleft = toFloatNode(left);
        FloatNode* fright = toFloatNode(right);
        result = calc_floats(fleft->value, fright->value, op_node->value);
      }
      else if(left->type == NODE_FLOAT && right->type == NODE_INT){
        FloatNode* fleft = toFloatNode(left);
        IntNode* iright = toIntNode(right);
        result = calc_floats(fleft->value, iright->value, op_node->value);
      }
      else if(left->type == NODE_INT && right->type == NODE_FLOAT){
        IntNode* ileft = toIntNode(left);
        FloatNode* fright= toFloatNode(right);
        result = calc_floats(ileft->value, fright->value, op_node->value);
      }
      return new FloatNode(result);
    }
  }
  else if(left->type == NODE_STRING && right->type == NODE_STRING){
    return new StringNode(toStringNode(left)->value + toStringNode(right)->value);
  }
  using namespace std::string_literals;
  this->error_message = "You can't make "s + op_node->value + " operation on "s;
  this->error_message += std::to_string(left->type) + " type and "s + std::to_string(right->type) + " type!\n"s;
  return nullptr;
}


