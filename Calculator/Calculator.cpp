#include "Calculator.h"
#include "Operators/StandardOps.h"

Calculator::Calculator()
  : pluginsPath("plugins")
{}

Calculator::Calculator(int argc, char* argv[]) 
  : Calculator() 
{
  if (argc > 1) 
    pluginsPath = argv[1];
}

void Calculator::loadOps() {
  this->opers.push_back(new Plus());
  this->opers.push_back(new Minus());
  this->opers.push_back(new Product());
  this->opers.push_back(new Division());
}

bool Calculator::init() {
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