#include "exp_calc/lexer.h"
#include "exp_calc/parser.h"
#include "exp_calc/node.h"
#include "exp_calc/interpreter.h"

#include <iostream>
#include <string>

void printErrorUnderine(const std::string raw_line, const size_t col, const size_t length){
  std::cout<<raw_line<< '\n';
  for(size_t i=0; i<raw_line.length(); i++){
    if(i < col || i > col + length)
      std::cout<<' ';
    else{
      std::cout<<'~';
    }
  }
  std::cout<<'\n';
}

int main(){
  std::string line;
  std::getline(std::cin, line);
  Lexer lexer(line);
  lexer.tokenize();
  if(!lexer.good()){
    std::cout<<lexer.getErrorMessage()<<std::endl;
    return EXIT_FAILURE;
  }
  for(Token t : lexer.getTokens()){
    std::cout<<t.toString()<<std::endl;
  }
  Parser parser(lexer.getTokens());
  parser.parse();
  std::cout << "Parsed: \n";
  parser.root_node->print();
  Interpreter interpreter(parser.popRootNode());
  Node* result = interpreter.interpret();
  std::cout<<"Wynik\n";
  result->print();
  if(result->type == NODE_ERROR){
    printErrorUnderine(line, result->col, toErrorNode(result)->length);
  }
  result->clear();

  return EXIT_SUCCESS;
}
