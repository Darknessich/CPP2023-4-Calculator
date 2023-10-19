#include "Calculator.h"

Calculator::Calculator(int argc, char* argv[]) 
  : pluginsPath(argc > 1? argv[1] : "plugins")
{
  auto plugins = solver.loadPlugins(this->pluginsPath);
  std::cout << "[ INFO] (" << plugins.first << " / " << plugins.second;
  std::cout << ") plugins loaded successfully" << std::endl;
}

int Calculator::exec(std::istream& is, std::ostream& os) {
  std::string exp, msg;
  bool check;

  os << "[ INFO] Available operators:" << std::endl;
  solver.printInfo(os);
  os << "[ INFO] Enter ^Z (EOF) for exit" << std::endl;
  std::getline(is, exp);
  while (!is.eof()) {
    double result = solver.calculate(exp, check, msg);
    if (check)
      os << "\t= " << result << std::endl;
    else
      os << "[ERROR] " << msg << std::endl;
    std::getline(is, exp);
  }

  return 0;
}