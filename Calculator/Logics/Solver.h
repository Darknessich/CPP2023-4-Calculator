#pragma once
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <iostream>
#include <unordered_map>

#include "../Operators/Operator.h"
#include "Parser.h"
#include "Validator.h"
#include "Flipper.h"

class Solver {
  using shToken = std::shared_ptr<Token>;
  using Tokens = std::vector<shToken>;
  using unqOperator = std::unique_ptr<Operator>;
  using Operators = std::unordered_map<std::string, unqOperator>;

  double calculateToken(shToken const& token, bool& ok, std::string& msg);
  double calculateState(bool& ok, std::string& msg);
public:
  Solver();
  
  std::pair<size_t, size_t> loadPlugins(std::string path);
  Operator* const getOperator(std::string const& name) const;
  void printInfo(std::ostream& os) const;
  double calculate(std::string const& expression, bool& ok, std::string& msg);

private:
  Parser parser;
  Validator validator;
  Flipper flipper;

  Tokens tokens;
  Operators operators;

  std::stack<double> values;
};