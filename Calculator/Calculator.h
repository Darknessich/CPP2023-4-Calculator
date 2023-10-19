#pragma once
#include <string>
#include <memory>
#include <iostream>

#include "Logics/Solver.h"

class Calculator {
public:
  Calculator(int argc = 0, char* argv[] = nullptr);
  int exec(std::istream& is = std::cin, std::ostream& os = std::cout);

private:  
  std::string pluginsPath;
  std::unique_ptr<Solver> solver;
};