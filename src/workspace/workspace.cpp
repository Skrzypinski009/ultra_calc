#include "workspace.h"
#include "table.h"
#include <iostream>
#include "../csv_support/csv_support.h"


Workspace::Workspace() : interpreter(&tables){
  // this->interpreter = Interpreter(tables&);
}

Workspace::~Workspace(){
  this->clearTables();
}

Table* Workspace::createTable(const size_t w, const size_t h){
  size_t id = this->tables.size() > 0 ? this->tables[this->tables.size()-1]->getId()+1 : 0;
  Table* t  = new Table(w, h, id);
  this->tables.push_back(t);
  return t;
}

Table* Workspace::getTable(const size_t idx) const{
   return idx < this->tables.size() ? this->tables[idx] : nullptr;
}

void Workspace::clearTables(){
  for(Table* t : this->tables) delete t;
}

void Workspace::parseCell(Cell* c){
  if(c->getParsedExpression()){
    c->getParsedExpression()->clear();
  }
  std::string text = c->getRawText();
  lexer.setLine(text);
  lexer.tokenize();
  if(!lexer.good()){
    std::cout<<lexer.getErrorMessage()<<std::endl;
  }
  
  parser.setTokens(lexer.getTokens());
  parser.parse();
  // parser.root_node->print();
  c->setParsedExpression(parser.popRootNode());
}

void Workspace::insertText(const size_t table_id, const size_t w, const size_t h, const std::string text){
  Table* t = this->getTable(table_id);
  t->insertCell(text, w, h);
  Cell* c = t->getCell(w, h);
  this->parseCell(c);
}

void Workspace::insertCol(const size_t table_id, const size_t col, std::string text){
  Table* t = this->getTable(table_id);
  t->insertCol(text, col);
  Cell* c = t->getColCell(col);
  this->parseCell(c);
}

void Workspace::insertRow(const size_t table_id, const size_t row, std::string text){
  Table* t = this->getTable(table_id);
  t->insertRow(text, row);
  Cell* c = t->getRowCell(row);
  this->parseCell(c);
}

void Workspace::calculate(){
  this->interpreter.interpretTables();
}

void Workspace::printTableRaw(const size_t table_id) const {
  this->getTable(table_id)->printTableRaw();
}

void Workspace::printTableCalculated(const size_t table_id) const {
  this->getTable(table_id)->printTableCalculated();
}

Table* Workspace::createTableFromCSV(const std::string& csv_path){
  std::vector<std::string>* lines = uc::csv::getLines(csv_path);
  Table* table = uc::csv::createTable(lines, this);
  delete lines;
  return table;
}

void Workspace::saveTableCSV(const std::string& csv_path, Table* table, const bool raw){
  std::vector<std::string>* lines = uc::csv::getLines(table, raw);
  uc::csv::saveTable(csv_path, lines);
  delete lines;
}

