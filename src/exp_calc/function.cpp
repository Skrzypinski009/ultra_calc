#include "function.h"
#include <ranges>
#include <algorithm>

Function::Function(bool args_limited, std::vector<std::vector<size_t>> args_types)
: args_limited(args_limited), args_types(args_types) {}

bool Function::checkArgs(std::vector<Node*>& args){
  if (this->args_limited){
    if (args.size() != this->args_types.size())
      return false;
    for (auto [idx, arg] : std::views::enumerate(args))
      if (!std::count(this->args_types[idx].begin(), this->args_types[idx].end(), arg->type))
        return false;
  } else
    for (Node* arg : args)
      if (!std::count(this->args_types[0].begin(), this->args_types[0].end(), arg->type))
        return false;
  return true;
}

// SUM //
Sum::Sum() : Function(false, {{NODE_INT, NODE_FLOAT}}) {}

Node* Sum::run(std::vector<Node*>& args){
  if (!this->checkArgs(args))
    return new ErrorNode(0, 0, "Wrong type");
  float sum = 0;
  for(Node* arg : args){
    sum += toFloatNode(arg)->value;
  }
  return new FloatNode(0, sum);
}

// AVG //
Avg::Avg() : Function(false, {{NODE_INT, NODE_FLOAT}}) {}

Node* Avg::run(std::vector<Node*>& args){
  if (!this->checkArgs(args))
    return new ErrorNode(0, 0, "Wrong type");
  float sum = 0;
  for(Node* arg : args){
    sum += toFloatNode(arg)->value;
  }
  return new FloatNode(0, sum/args.size());
}

