#pragma once
class Table;

#include "cell.h"
#include "../exp_calc/lexer.h"
#include "../exp_calc/parser.h"
#include "../exp_calc/interpreter.h"

class Table{
  Cell** cells;
  size_t width;
  size_t height;

  Lexer* lexer;
  Parser* parser;
  Interpreter* interpreter;
public:
  Table(const size_t width, const size_t height, Lexer* lexer, Parser* parser, Interpreter* interpreter);
  ~Table();
  void createCells();
  void clearCells();
  Cell* getCell(const size_t w, const size_t h);
  void insertText(const std::string text, const size_t w, const size_t h);
  void parseCell(const size_t w, const size_t h);
  void interpretCell(const size_t w, const size_t h);
  std::string getCellResult(const size_t w, const size_t h);
};

