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
  Workspace workspace;
  workspace.createTable(2, 4);
  // col 0
  workspace.insertText(0,0,0, "T+2");   workspace.insertText(0,1,0);
  workspace.insertText(0,0,1);        workspace.insertText(0,1,1, "TC-R- +3");
  workspace.insertText(0,0,2);        workspace.insertText(0,1,2, "R- +2");
  workspace.insertText(0,0,3);        workspace.insertText(0,1,3);
  // col 1
  

  workspace.calculate();
  std::cout<<"Table1\n";
  workspace.printTableRaw(0);
  std::cout<<"\n";
  workspace.printTableCalculated(0);

  return EXIT_SUCCESS;
}
