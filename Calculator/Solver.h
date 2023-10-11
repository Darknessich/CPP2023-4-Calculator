#pragma once
#include <string>
#include <vector>

#include "Operators/Operator.h"

class Solver {
public:
  Solver();
  
  size_t loadPlugins(std::string path);
  double calculate(std::string expression, double prev = 0.0);

private:
  std::vector<Operator*> operators;

};