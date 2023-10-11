#pragma once
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

#include "Parser.h"
#include "Operators/Operator.h"

class Solver {
  std::vector<Token*> reverseExpression(std::vector<Token*> const& tokens);
public:
  Solver();
  
  size_t loadPlugins(std::string path);
  double calculate(std::string const& expression);

private:
  Parser parser;
  std::vector<Token*> tokens;
  std::unordered_map<std::string, Operator*> operators;

  std::stack<double> values;
};