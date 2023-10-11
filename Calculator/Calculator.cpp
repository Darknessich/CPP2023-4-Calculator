#include "Calculator.h"

auto& debug = std::cout;

Calculator::Calculator(int argc, char* argv[]) 
  : pluginsPath(argc > 1? argv[1] : "plugins"), solver()
{}

bool Calculator::init() {
  auto& debug = std::cout;
  debug << "load " << solver.loadPlugins(pluginsPath) << " plugins" << std::endl;
  
  return true;
}

int Calculator::exec(std::istream& is, std::ostream& os) {
  os << "Enter ^Z (EOF) for exit" << std::endl;
  std::string exp;
  std::getline(is, exp);
  while (!is.eof()) {
    os << exp << std::endl;
    std::getline(is, exp);
  }

  return 0;
}