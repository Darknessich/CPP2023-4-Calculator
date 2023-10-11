#pragma once
#include <string>
#include <iostream>

#include "Solver.h"

class Calculator {
public:
  Calculator(int argc = 0, char* argv[] = nullptr);

  int exec(std::istream& is = std::cin, std::ostream& os = std::cout);

private:  
  std::string pluginsPath;
  Solver solver;
};