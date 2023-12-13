#include <string>
#include <iostream>

#include "parser.h"
#include "lexer.h" // Token
#include "node.h"

Parser::Parser(){
  this->idx = 0;
  root_node = nullptr;
}

Parser::~Parser(){
  if(root_node != nullptr)
    root_node->clear();
}

void Parser::setTokens(const std::vector<Token> tokens){
  this->tokens = tokens;
  this->idx = 0;
  if(root_node != nullptr)
    root_node->clear();
}

Token Parser::at() const{
  return this->tokens[this->idx];
}

bool Parser::eat(size_t token_type = -1){
  if(token_type == -1 || this->at().type == token_type){
    this->idx +=1;
    return true;
  }
  return false;
}

bool Parser::isEOL(){
  return this->idx >= this->tokens.size() ? true: false;
}

void Parser::clear(){
  this->root_node = this->root_node->clear();
}

Node* Parser::popRootNode(){
  Node* root_node = this->root_node;
  this->root_node = nullptr;
  return root_node;
}

bool Parser::addCondition(){
  return !this->isEOL() && 
    (
      this->at().type == TOKEN_OPERATOR && 
      *(this->at().value) == "+" || 
      *(this->at().value) == "-"
    );
}

bool Parser::mulCondition(){
  return !this->isEOL() &&
    (
      (this->at().type == TOKEN_OPERATOR && 
      *(this->at().value) == "*") || 
      *(this->at().value) == "/"
    );
}

void Parser::parse(){
  this->root_node = this->parseAdd();
}

Node* Parser::parseAdd(){
  Node* left_side = this->parseMul();
  while(this->addCondition()){
    char op = (*(this->at().value))[0];
    size_t col = this->at().col;
    this->eat();
    // std::cout<<"adding\n";
    // std::cout<<"LEFT SIDE\n";
    // left_side->print();
    // std::cout<<this->at().type<<std::endl;
    Node* right_side = this->parseAdd();
    // std::cout<<"RIGHT SIDE\n";
    // right_side->print();
    left_side = new OperatorNode(col, op, left_side, right_side);
  }
  // std::cout<<"returning ls\n";
  // left_side->print();
  return left_side;
}

Node* Parser::parseMul(){
  Node* left_side = this->parseFactor();
  while(this->mulCondition()){
    // std::cout<<"multiplication\n";
    char op = (*(this->at().value))[0];
    size_t col = this->at().col;
    this->eat();
    Node* right_side = this->parseMul();
    left_side = new OperatorNode(col, op, left_side, right_side);
  }
  // std::cout<<"returning ls\n";
  return left_side;
}

Node* Parser::parseFactor(){
  Node* left_side = nullptr;
  std::string value;
  // std::cout<<Token::typeString(this->at().type)<<std::endl;
  // std::cout<<"getting factor\n";
  size_t col = this->at().col;
  switch(this->at().type){
    case TOKEN_INT:
      value = *(this->at().value);
      left_side = new IntNode(col, stoi(value));
      this->eat();
      break;
    case TOKEN_FLOAT:
      value = *(this->at().value);
      left_side = new FloatNode(col, stof(value));
      this->eat();
      break;
    case TOKEN_STRING:
      left_side = new StringNode(col, *(this->at().value));
      this->eat();
      break;
    case TOKEN_L_BRACKET:
      this->eat();
      left_side = this->parseAdd();
      if(!this->eat(TOKEN_R_BRACKET)){
        std::cout<<"no r bracket error at " << this->idx-1 <<"! \n";
      }
      break;
    case TOKEN_WORD:
      std::string name = *(this->at().value);
      this->eat();
      std::vector<Node*> args;
      while(this->at().type == TOKEN_COMMA || this->at().type == TOKEN_L_BRACKET){
        this->eat();
        args.push_back(this->parseAdd());
      }
      size_t end = this->idx;
      this->eat();
      left_side = new FunctionNode(col, end-col, name, args);
      break;
  }
  // std::cout<<"returning factor\n";
  return left_side;
}
