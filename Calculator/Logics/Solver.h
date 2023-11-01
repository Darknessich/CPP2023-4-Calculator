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
  template<class T>
  using uptr = std::unique_ptr<T>;

  using shToken = std::shared_ptr<Token>;
  using Tokens = std::vector<shToken>;
  using Operators = std::unordered_map<std::string, uptr<Operator>>;

  double calculateToken(shToken const& token, bool& ok, std::string& msg);
  double calculateState(bool& ok, std::string& msg);
public:
  Solver();
  
  std::pair<size_t, size_t> loadPlugins(std::string path);
  Operator* const getOperator(std::string const& name) const;
  void printInfo(std::ostream& os) const;
  double calculate(std::string const& expression, bool& ok, std::string& msg);

private:
  uptr<Parser> parser;
  uptr<Validator> validator;
  uptr<Flipper> flipper;

  Tokens tokens;
  Operators operators;

  std::stack<double> values;
};