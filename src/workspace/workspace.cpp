#include "workspace.h"
#include "table.h"


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

void Workspace::insertText(const std::string text, const size_t table_id, const size_t w, const size_t h){
  Table* t = this->getTable(table_id);
  t->insertText(text, w, h);
  Cell* c = t->getCell(w, h);
  if(c->getParsedExpression()){
    c->getParsedExpression()->clear();
  }
  // std::string text = c->getRawText();
  lexer.setLine(text);
  lexer.tokenize();
  parser.setTokens(lexer.getTokens());
  parser.parse();
  // parser.root_node->print();
  c->setParsedExpression(parser.popRootNode());
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
