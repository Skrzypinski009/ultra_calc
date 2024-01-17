#include "utils.h"
#include <string>
#include <vector>

std::vector<std::string>* uc::splitString(const std::string& text, const char separator){
  std::vector<std::string>* elements = new std::vector<std::string>;
  std::string buffor;
  for(char c : text){
    if(c == separator){
      elements->push_back(buffor);
      buffor = "";
    } else
      buffor += c;
  }
  elements->push_back(buffor);
  return elements;
}
