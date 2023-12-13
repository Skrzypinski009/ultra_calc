#include "exp_calc/lexer.h"
#include "exp_calc/parser.h"
#include "exp_calc/node.h"
#include "exp_calc/interpreter.h"
#include "workspace/table.h"
#include "workspace/cell.h"

#include <iostream>
#include <string>

// void printErrorUnderine(const std::string raw_line, const size_t col, const size_t length){
//   std::cout<<raw_line<< '\n';
//   for(size_t i=0; i<raw_line.length(); i++){
//     if(i < col || i > col + length)
//       std::cout<<' ';
//     else{
//       std::cout<<'~';
//     }
//   }
//   std::cout<<'\n';
// }

int main(){
  // std::string line;
  // std::getline(std::cin, line);
  Lexer lexer;
  Parser parser;
  Interpreter interpreter;

  Table t1(4,4, &lexer, &parser, &interpreter);
  Cell* c = t1.getCell(0,0);
  t1.insertText("4 + 4", 0,0);
  std::cout<<c->getRawText()<<" = ";
  std::cout<<t1.getCellResult(0,0)<<"\n";

  t1.insertText("4 - 68", 0,0);
  std::cout<<c->getRawText()<<" = ";
  std::cout<<t1.getCellResult(0,0)<<"\n";

  return EXIT_SUCCESS;
}
