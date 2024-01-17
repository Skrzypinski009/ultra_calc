#pragma once
class Workspace;
#include "table.h"
#include "../exp_calc/lexer.h"
#include "../exp_calc/parser.h"
#include "../exp_calc/interpreter.h"
#include "../csv_support/csv_support.h"

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
  void parseCell(Cell* c);
  void insertText(const size_t table_id, const size_t w, const size_t h, const std::string text = "");
  void insertCol(const size_t table_id, const size_t col, const std::string text = "");
  void insertRow(const size_t table_id, const size_t row, const std::string text = "");
  void printTableRaw(const size_t table_id) const; 
  void printTableCalculated(const size_t table_id) const; 
  Table* createTableFromCSV(const std::string& csv_path);
  void saveTableCSV(const std::string& csv_path, Table* table, const bool raw);
};
