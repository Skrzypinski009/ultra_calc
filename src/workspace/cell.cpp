#include "cell.h"
#include <iostream>

Cell::Cell(Table* parent, const std::string raw_text){
  this->raw_text = raw_text;
  this->parent = parent;
}

Cell::Cell(){
  this->parent = nullptr;
  this->result_node = nullptr;
  this->parsed_exp = nullptr;
  this->raw_text = "";
}

Cell::~Cell(){
  this->clear();
}

void Cell::clear(){
  this->parent = nullptr;
  if(this->result_node != nullptr)
    this->result_node->clear();
  if(this->parsed_exp != nullptr)
    this->parsed_exp->clear();
}

std::string Cell::getResultString(){
  if(this->getResultNode() == nullptr)
    return "";
  return getResultNode()->getValueString();
}

void Cell::setRawText(const std::string raw_text){
  this->raw_text = raw_text;
  if(this->parsed_exp != nullptr)
    this->parsed_exp->clear();
  if(this->result_node != nullptr)
    this->result_node->clear();
}

std::string Cell::getRawText() const{
  return this->raw_text;
}

void Cell::setParsedExpression(Node* parsed_exp){
  this->parsed_exp = parsed_exp;
}

Node* Cell::getParsedExpression() const {
  return this->parsed_exp;
}

void Cell::setResultNode(Node* result_node){
  this->result_node = result_node;
}

Node* Cell::getResultNode() const {
  return this-> result_node;
}

