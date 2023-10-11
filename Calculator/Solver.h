#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Parser.h"
#include "Operators/Operator.h"

class Solver {
public:
  Solver();
  
  size_t loadPlugins(std::string path);
  double calculate(std::string const& expression, double prev = 0.0);

private:
  Parser parser;
  std::vector<Token*> tokens;
  std::unordered_map<std::string, Operator*> operators;
};