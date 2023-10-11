#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Operators/Operator.h"

class Calculator {
public:
  Calculator();
  Calculator(int argc, char* argv[]);

  bool init();
  int exec(std::istream& is = std::cin, std::ostream& os = std::cout);
  std::vector<Operator*> const& getOperators();

private:
  void loadOps();

  std::string pluginsPath;
  std::vector<Operator*> opers;
};