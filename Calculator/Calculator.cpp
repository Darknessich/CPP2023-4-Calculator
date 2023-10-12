#include "Calculator.h"
#include "Loader.h"

Calculator::Calculator(int argc, char* argv[]) 
  : pluginsPath(argc > 1? argv[1] : "plugins")
{
  size_t plugins = 0;

  try {
    plugins = solver.loadPlugins(this->pluginsPath);
    std::cout << "[ INFO] " << plugins << " plugins loaded successfully" << std::endl;
  } catch (LoaderErr& err) {
    std::cerr << "[ERROR] " << err.what() << std::endl;
    throw;
  }
}

int Calculator::exec(std::istream& is, std::ostream& os) {
  os << "[ INFO] Enter ^Z (EOF) for exit" << std::endl;
  std::string exp;
  std::getline(is, exp);
  while (!is.eof()) {
    try {
      double result = solver.calculate(exp);
      os << "\t= " << result << std::endl;
    } catch (SolverErr& err) {
      os << "[ERROR] " << err.what() << std::endl;
    }
    std::getline(is, exp);
  }

  return 0;
}