#pragma once
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <exception>
#include <unordered_map>

#include "Parser.h"
#include "Operators/Operator.h"

class SolverErr : public std::exception {
public:
  using std::exception::exception;
};

class Solver {
  using shptrT = std::shared_ptr<Token>;
  using shptrOp = std::shared_ptr<Operator>;

  std::vector<shptrT> reverseExpression(std::vector<shptrT> const& tokens);
  void clearStack();
public:
  Solver();
  
  size_t loadPlugins(std::string path);
  double calculate(std::string const& expression);

private:
  Parser parser;
  std::vector<shptrT> tokens;
  std::unordered_map<std::string, shptrOp> operators;

  std::stack<double> values;
};