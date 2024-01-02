#include "interpreter.h"
#include "../utils/utils.h"
#include "node.h"
#include "function_manager.h"
#include <string>
#include <iostream>
#include <cstdlib>
// Node* Interpreter::interpret(Node* node_tree){
//   Node* node_copy = node_tree->duplicate();
//   if(node_copy){
//     return interpretNode(node_copy);
//   }
//   return new ErrorNode(0, 0, "Empty tree\n");
// }

Interpreter::Interpreter(std::vector<Table*>* tables){
  this->tables = tables;
}

Interpreter::~Interpreter(){}

void Interpreter::interpretTables(){
  for(size_t i=0; i<this->tables->size(); i++){
    this->interpretTable(this->tables->at(i));
  }
}

void Interpreter::interpretTable(Table* table){
  for(size_t w=0; w<table->getWidth(); w++){
    for(size_t h=0; h<table->getHeight(); h++){
      Cell* c = table->getCell(w,h);
      this->interpretCell(table, w, h);
    }
  }
}

void Interpreter::interpretCell(Table* table, const size_t w, const size_t h){
  if(w < table->getWidth() && h < table->getHeight()){
    Cell* c = table->getCell(w,h);
    if(c->getParsedExpression() == nullptr){
      Cell* col_cell = table->getColCell(w);
      Cell* row_cell = table->getRowCell(h);
      if(col_cell != nullptr){
        Node* col_exp = col_cell->getParsedExpression();
        c->setResultNode(this->interpretNode(col_exp->duplicate(), table->getId(), w, h));
      } else if(row_cell != nullptr){
        Node* row_exp = row_cell->getParsedExpression();
        c->setResultNode(this->interpretNode(row_exp->duplicate(), table->getId(), w, h));
      }
    } else {
      c->setResultNode(this->interpretNode(c->getParsedExpression()->duplicate(), table->getId(), w, h));
      c->getParsedExpression()->print();
    }
  }
}

Node* Interpreter::interpretNode(Node* node, const size_t table_id, const size_t w, const size_t h){
  if(
    node->type == NODE_INT || 
    node->type == NODE_FLOAT || 
    node->type == NODE_STRING ||
    node->type == NODE_ERROR
  ){
    return node;
  } 
  else if(node->type == NODE_OPERATOR){
    OperatorNode* op = toOperatorNode(node);
    op->left_side = this->interpretNode(op->left_side, table_id, w, h);
    op->right_side = this->interpretNode(op->right_side, table_id, w, h);
    Node* result = this->interpretOperator(op);
    op->clear();
    return result;
  }
  else if(node->type == NODE_FUNCTION){
    FunctionNode* func = toFunctionNode(node);
    std::vector<Node*> r_args;
    for(Node* arg: func->args){
      r_args.push_back(interpretNode(arg, table_id, w, h));
    }
    return FunctionManager::getFunction(func->name)->run(r_args);
  } else if(node->type == NODE_RELATION){
    RelationNode* rel = toRelationNode(node);
    size_t r = h;
    size_t c = w;
    size_t t = table_id;
    //table
    if(rel->t_val[0] == '+'){
      if(rel->t_val.length() == 1)
        t += 1;
      else
        t += std::stoi(rel->t_val.substr(1,rel->t_val.length()));
    } else if(rel->t_val[0] == '-'){
      if(rel->t_val.length() == 1)
        t -= 1;
      else
        t -= std::stoi(rel->t_val.substr(1,rel->t_val.length()));
    } else{
      t = std::stoi(rel->t_val);
    }
    // row
    if(rel->r_val[0] == '+'){
      if(rel->r_val.length() == 1)
        r += 1;
      else
        r += std::stoi(rel->r_val.substr(1,rel->r_val.length()));
    } else if(rel->r_val[0] == '-'){
      if(rel->r_val.length() == 1)
        r -= 1;
      else
        r -= std::stoi(rel->r_val.substr(1,rel->r_val.length()));
    } else{
      r = std::stoi(rel->r_val);
    }
    // column
    if(rel->c_val[0] == '+'){
      if(rel->c_val.length() == 1)
        c += 1;
      else
        c += std::stoi(rel->c_val.substr(1,rel->c_val.length()));
    } else if(rel->c_val[0] == '-'){
      if(rel->c_val.length() == 1)
        c -= 1;
      else
        c -= std::stoi(rel->c_val.substr(1,rel->c_val.length()));
    } else{
      c = std::stoi(rel->c_val);
    }
    if(this->tables->size() <= t)
      return new ErrorNode(rel->col, rel->length, "Cell is out of range");
    Table* table = this->tables->at(t);

    if(table->getWidth() <= c || table->getHeight() <= r)
      return new ErrorNode(rel->col, rel->length, "Cell is out of range");
    Cell* cell = table->getCell(c, r);

    Node* res_n = cell->getResultNode();
    
    if(res_n != nullptr) 
    {
      if(res_n->type == NODE_ERROR){
        return new ErrorNode(rel->col, rel->length, "Relation has Error");
      }
      Node* n = res_n->duplicate(); //error
      return n;
    }

    if(cell->getParsedExpression() != nullptr){
      this->interpretCell(this->tables->at(t), c, r);
      return cell->getResultNode()->duplicate();
    }
    return new ErrorNode(rel->col, rel->length, "Relation Error");
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
  if(op_node->value == '&'){
    if (left->type == NODE_ERROR) return right->duplicate();
    return left->duplicate();
  }
  if(
    (left->type == NODE_INT || left->type == NODE_FLOAT) && 
    (right->type == NODE_FLOAT || right->type == NODE_INT)
  ){
    if(left->type == NODE_INT && right->type == NODE_INT){
      IntNode* ileft = toIntNode(left);
      IntNode* iright = toIntNode(right);
      if(op_node->value == '/'){
        if(iright->value == 0){
          return new ErrorNode(left->col, right->col - left->col, "Can't divide by 0!\n");
        }
        float result = ileft->value/(float)(iright->value);
        return new FloatNode(left->col, right->col + right->length - left->col, result);
      }
      int result = calc_ints(ileft->value, iright->value, op_node->value);
      return new IntNode(left->col, right->col + right->length - left->col, result);
    }
    else{
      float result = 0;
      // std::cout<<left->type<<", "<<right->type<<std::endl;
      if(
        (op_node->value == '/') &&
        (right->type == NODE_INT && toIntNode(right)->value == 0) ||
        (right->type == NODE_FLOAT && toFloatNode(right)->value == 0)
      ){
        return new ErrorNode(op_node->col, right->col + right->length - left->col, "Can't divide by 0!\n");
      }
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
      return new FloatNode(left->col, right->col + right->length - left->col, result);
    }
  }
  else if(left->type == NODE_STRING && right->type == NODE_STRING){
    return new StringNode(left->col, right->col + right->length - left->col, toStringNode(left)->value + toStringNode(right)->value);
  }
  else {
    if(left->type == NODE_ERROR){
      return new ErrorNode(left->col, toErrorNode(left)->length, toErrorNode(left)->content);
    }
    if(right->type == NODE_ERROR){
      return new ErrorNode(right->col, toErrorNode(right)->length, toErrorNode(right)->content);
    }
  }

  using namespace std::string_literals;
  return new ErrorNode(
    left->col,
    right->col + right->length - left->col,
    "Can't make '"s + op_node->value + "' operation on " + 
    Node::toString(left->type) + " and " + Node::toString(right->type) + "!\n"
  );
}


