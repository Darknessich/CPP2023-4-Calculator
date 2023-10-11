#include "Solver.h"
#include "Loader.h"
#include "Operators/StandardOps.h"

Solver::Solver() {
  for (auto op : getStandardOps()) {
    this->operators[op->getName()] = op;
    this->parser.addName(op->getName());
  }
}

size_t Solver::loadPlugins(std::string path) {
  Loader loader(path);
  size_t cnt = 0;

  for (Operator* op = loader.get(); op != nullptr; op = loader.next(), cnt++) {
    this->operators[op->getName()] = op;
    this->parser.addName(op->getName());
  }

  return cnt;
}

double Solver::calculate(std::string const& exp, double prev) {
  this->tokens = parser.parse(exp);

  return 0.0;
}