#pragma once
class Table;
#include "cell.h"

class Table{
  Cell** cells;
  size_t width;
  size_t height;
  size_t id;
public:
  Table(const size_t width, const size_t height, const size_t id);
  ~Table();
  size_t getId() const;
  size_t getWidth() const;
  size_t getHeight() const;
  void createCells();
  void clearCells();
  Cell* getCell(const size_t w, const size_t h);
  void insertText(const std::string text, const size_t w, const size_t h);
  // void parseCell(const size_t w, const size_t h);
  // void interpretCell(const size_t w, const size_t h);
  std::string getCellResult(const size_t w, const size_t h);
  void printTableRaw() const;
  void printTableCalculated() const;
};

