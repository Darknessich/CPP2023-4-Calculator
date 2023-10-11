#include "Calculator.h"

Calculator::Calculator(int argc, char* argv[]) 
  : pluginsPath(argc > 1? argv[1] : "plugins"), solver()
{
#ifndef NDEBUG
  std::cout << "load " << solver.loadPlugins(this->pluginsPath) << " plugins" << std::endl;
#else
  solver.loadPlugins(this->pluginsPath);
#endif
}

int Calculator::exec(std::istream& is, std::ostream& os) {
  os << "Enter ^Z (EOF) for exit" << std::endl;
  std::string exp;
  std::getline(is, exp);
  while (!is.eof()) {
    os << "\t= " <<  solver.calculate(exp) << std::endl;
    std::getline(is, exp);
  }

  return 0;
}