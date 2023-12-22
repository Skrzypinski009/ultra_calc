#include "exp_calc/lexer.h"
#include "exp_calc/parser.h"
#include "exp_calc/node.h"
#include "exp_calc/interpreter.h"
#include "workspace/table.h"
#include "workspace/cell.h"
#include "workspace/workspace.h"

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
  Workspace workspace;
  workspace.createTable(2,2);
  workspace.insertText("2 + 2", 0,0,0);
  workspace.insertText("8*(5+4.4)", 0,1,0);
  workspace.insertText("(8+8)/3", 0,0,1);
  workspace.insertText("1/4", 0,1,1);

  workspace.createTable(2,2);
  workspace.insertText("10 - 20", 1,0,0);
  workspace.insertText("8*7*9", 1,1,0);
  workspace.insertText("121/11", 1,0,1);
  workspace.insertText("1/8", 1,1,1);


  workspace.calculate();
  std::cout<<"Table1\n";
  workspace.printTableRaw(0);
  std::cout<<"\n";
  workspace.printTableCalculated(0);
  std::cout<<"\n\n";
  std::cout<<"Table2\n";
  workspace.printTableRaw(1);
  std::cout<<"\n";
  workspace.printTableCalculated(1);

  return EXIT_SUCCESS;
}
