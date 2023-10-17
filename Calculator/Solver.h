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
  using shToken = std::shared_ptr<Token>;
  using Tokens = std::vector<shToken>;
  using unqOperator = std::unique_ptr<Operator>;

  Tokens reverseExpression(Tokens const& tokens);
  void clearStack();
public:
  Solver();
  
  std::pair<size_t, size_t> loadPlugins(std::string path);
  double calculate(std::string const& expression);

private:
  Parser parser;
  Tokens tokens;
  std::unordered_map<std::string, unqOperator> operators;

  std::stack<double> values;
};