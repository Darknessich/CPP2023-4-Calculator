#include "Solver.h"
#include "Loader.h"
#include "Operators/StandardOps.h"

Solver::Solver() {
  for (auto op : getStandardOps())
    operators.push_back(op);
}

size_t Solver::loadPlugins(std::string path) {
  Loader loader();

  return 0;
}