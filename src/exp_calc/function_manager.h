#pragma once
#include "function.h"
#include <utility>
#include <memory>
#include <map>

class FunctionManager{
  static std::map<std::string, std::shared_ptr<Function>> functions;
public:
  static Function* getFunction(const std::string name);
};
