#pragma once

#include "node.h"
#include <vector>

class Function{
  bool args_limited;
  std::vector<std::vector<size_t>> args_types;
public:
  Function(bool args_limited, std::vector<std::vector<size_t>> args_types);
  bool checkArgs(std::vector<Node*>& args);
  virtual Node* run(std::vector<Node*>& args) {return nullptr;}
};

// SUM //
class Sum: public Function{
public:
  Sum();
  Node* run(std::vector<Node*>& args) override;
};

// AVG //
class Avg: public Function{
public:
  Avg();
  Node* run(std::vector<Node*>& args) override;
};

