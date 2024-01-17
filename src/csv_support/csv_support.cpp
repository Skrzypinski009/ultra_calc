#include "csv_support.h"
#include "../workspace/table.h"
#include "../workspace/workspace.h"
#include "../utils/utils.h"
#include <string>
#include <vector>
#include <fstream>
#include <ranges>
#include <iostream>


std::vector<std::string>* uc::csv::getLines(std::string csv_path){
  std::vector<std::string>* lines = new std::vector<std::string>;
  std::string buffor;
  std::ifstream file(csv_path); //with file opened
  if (!file){
    std::cout<<"Can't open file\n";
    return nullptr;
  }
  while(getline(file, buffor)){
    lines->push_back(buffor);
  } 
  return lines;
}

Table* uc::csv::createTable(std::vector<std::string>* lines, Workspace* workspace){
  size_t w, h = lines->size();
  { // getting table width
    std::string line0 = lines->at(0);
    std::vector<std::string>* splitted = uc::splitString(line0, ';');
    w = splitted->size();
    delete splitted;
  }

  Table* table = workspace->createTable(w, h);
  
  for(size_t ih : std::views::iota(0, (int)h)){
    std::string line = lines->at(ih);
    std::vector<std::string>* splitted = uc::splitString(line, ';');
    for(size_t iw : std::views::iota(0, (int)w))
      workspace->insertText(table->getId(), iw, ih, splitted->at(iw));
    delete splitted;
  }
  return table;
}

