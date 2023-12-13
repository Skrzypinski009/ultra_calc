#include "table.h"

Table::Table(const size_t width, const size_t height, Lexer* lexer, Parser* parser, Interpreter* interpreter){
  this->width = width;
  this->height = height;
  this->createCells();

  this->lexer = lexer;
  this->parser = parser;
  this->interpreter = interpreter;
}

Table::~Table(){
  this->clearCells();
}

void Table::createCells(){
  this->cells = new Cell*[width];
  for(size_t i=0; i<width; i++){
    this->cells[i] = new Cell[height];
  }
}

void Table::clearCells(){
  if(this->cells != nullptr){
    for(size_t i=0; i<width; i++){
      if(this->cells[i] != nullptr){
        for(size_t j=0; j<height; j++){
          this->cells[i][j].clear();
        }
        delete [] this->cells[i];
      }
    }
    delete [] this->cells;
  }
}

Cell* Table::getCell(const size_t w, const size_t h){
  if(!(w < this->width && h < this->height))
    return nullptr;

  return &(this->cells[w][h]);
}

void Table::insertText(const std::string text, const size_t w, const size_t h){
  if(!(w < this->width && h < this->height))
    return;

  this->cells[w][h].setRawText(text);
  this->parseCell(w, h);
  this->interpretCell(w, h);
}

void Table::parseCell(const size_t w, const size_t h){
  if(this->cells[w][h].getParsedExpression()){
    this->cells[w][h].getParsedExpression()->clear();
  }
  std::string text = this->cells[w][h].getRawText();
  lexer->setLine(text);
  lexer->tokenize();
  parser->setTokens(lexer->getTokens());
  parser->parse();
  // parser->root_node->print();
  this->cells[w][h].setParsedExpression(parser->popRootNode());
}

void Table::interpretCell(const size_t w, const size_t h){
  if(cells[w][h].getResultNode()){
    cells[w][h].getResultNode()->clear();
  }
  cells[w][h].setResultNode(
    this->interpreter->interpret(
      cells[w][h].getParsedExpression()
    )
  );
}

std::string Table::getCellResult(const size_t w, const size_t h){
  if(!(w < this->width && h < this->height))
    return "";

  return cells[w][h].getResultString();
}

