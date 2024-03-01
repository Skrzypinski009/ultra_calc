#include "table.h"
#include <string>
#include <iostream>

Table::Table(const size_t width, const size_t height, const size_t id){
  this->width = width;
  this->height = height;
  this->id = id;
  this->createCells();
}

Table::~Table(){
  this->clearCells();
}

size_t Table::getId() const{
  return this->id;
}

size_t Table::getWidth() const{
  return this->width;
}

size_t Table::getHeight() const{
  return this->height;
}

void Table::createCells(){
  this->cells = new Cell*[this->width];
  for(size_t i=0; i<this->width; i++){
    this->cells[i] = new Cell[this->height];
  }
}

void Table::clearCells(){
  if(this->cells != nullptr){
    for(size_t i=0; i<this->width; i++){
      if(this->cells[i] != nullptr){
        for(size_t j=0; j<this->height; j++){
          this->cells[i][j].clear();
        }
        delete [] this->cells[i];
      }
    }
    delete [] this->cells;
  }
}

Cell* Table::getCell(const size_t w, const size_t h){
  if(!(w < this->width && h < this->height)){
    return nullptr;
    std::cout<<"Cell"<<w<<" "<<h<<" is out of range\n";
  }

  // std::cout<<"Cell "<<w<<" "<<h<<"\n";
  return &(this->cells[w][h]);
}

void Table::insertCell(const std::string text, const size_t w, const size_t h){
  if(!(w < this->width && h < this->height))
    return;

  this->cells[w][h].setRawText(text);
}

void Table::insertCol(const std::string text, const size_t col){
  if(this->col_cells.find(col) != this->col_cells.end()){
    this->col_cells.at(col)->setRawText(text);
    return;
  }
  this->col_cells[col] = new Cell(this, text);
}

void Table::insertRow(const std::string text, const size_t row){
  if(this->row_cells.find(row) != this->row_cells.end()){
    this->row_cells.at(row)->setRawText(text);
    return;
  }
  this->row_cells[row] = new Cell(this, text);
}

Cell* Table::getColCell(const size_t col) const {
  if(this->col_cells.find(col) != this->col_cells.end()){
    return (this->col_cells).at(col);
  }
  return nullptr;
}

Cell* Table::getRowCell(const size_t row) const {
  if(this->row_cells.find(row) != this->row_cells.end()){
    return (this->row_cells).at(row);
  }
  return nullptr;
}

// void Table::parseCell(const size_t w, const size_t h){
//   if(this->cells[w][h].getParsedExpression()){
//     this->cells[w][h].getParsedExpression()->clear();
//   }
//   std::string text = this->cells[w][h].getRawText();
//   lexer->setLine(text);
//   lexer->tokenize();
//   parser->setTokens(lexer->getTokens());
//   parser->parse();
//   // parser->root_node->print();
//   this->cells[w][h].setParsedExpression(parser->popRootNode());
// }
//
// void Table::interpretCell(const size_t w, const size_t h){
//   if(cells[w][h].getResultNode()){
//     cells[w][h].getResultNode()->clear();
//   }
//   cells[w][h].setResultNode(
//     this->interpreter->interpret(
//       cells[w][h].getParsedExpression()
//     )
//   );
// }
//
// std::string Table::getCellRaw(const size_t w, const size_t h){
//   if(!(w < this->width && h < this->height))
//     return "";
//
//   return this->cells[w][h].getRawText();
// }
//
std::string Table::getCellResult(const size_t w, const size_t h){
  if(!(w < this->width && h < this->height))
    return "";

  return this->cells[w][h].getResultString();
}

// vector<std::string> getRowRaw(const size_t row){
// 	vector<std::string> row(this->widht);
// 	for(size_t w=0; w<this->width; w++){
// 		row[w] = this->getCellRaw(w, h);
// 	}
// 	return row;
// }
//
// vector<std::string> getRowResult(const size_t row){
//
// }

void Table::printTableRaw() const {
  for(size_t h=0; h<this->height; h++){
    for(size_t w=0; w<this->width; w++){
      std::string text = this->cells[w][h].getRawText();
      if(text == ""){
        if(this->getColCell(w)){
          text = getColCell(w)->getRawText();
        } else if(this->getRowCell(h)){
          text = getRowCell(h)->getRawText();
        }
      }
      std::cout<<text;
      std::cout<<"  |";
    }
    std::cout<<'\n';
  }
}

void Table::printTableCalculated() const {
  for(size_t h=0; h<this->height; h++){
    for(size_t w=0; w<this->width; w++){
      std::cout<<this->cells[w][h].getResultString();
      std::cout<<"  |";
    }
    std::cout<<'\n';
  }
}
