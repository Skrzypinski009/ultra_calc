#include "exp_calc/lexer.h"
#include "exp_calc/parser.h"
#include "exp_calc/node.h"
#include "exp_calc/interpreter.h"

#include <iostream>
#include <string>

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
  result->clear();

  return EXIT_SUCCESS;
}
