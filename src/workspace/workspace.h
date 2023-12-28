#pragma once
#include "table.h"
#include "../exp_calc/lexer.h"
#include "../exp_calc/parser.h"
#include "../exp_calc/interpreter.h"

class Workspace{
  std::vector<Table*> tables;
  Lexer lexer;
  Parser parser;
  Interpreter interpreter;
public:
  Workspace();
  ~Workspace();
  Table* createTable(const size_t w, const size_t h);
  Table* getTable(const size_t idx) const;
  void clearTables();
  void calculate();
  void insertText(const size_t table_id, const size_t w, const size_t h, const std::string text = "");
  void printTableRaw(const size_t table_id) const; 
  void printTableCalculated(const size_t table_id) const; 
};
