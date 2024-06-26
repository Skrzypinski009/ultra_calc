#include "function_manager.h"

std::map<std::string, std::shared_ptr<Function>> FunctionManager::functions = {
  {"sum", std::make_shared<Sum>()},
  {"avg", std::make_shared<Avg>()}
};

Function* FunctionManager::getFunction(const std::string name){
  if (functions.find(name) != functions.end())
    return functions.at(name).get();
  return nullptr;
}
