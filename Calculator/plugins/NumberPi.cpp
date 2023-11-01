#define _USE_MATH_DEFINES
#include <cmath>

#include "../Operators/Operator.h"

class NumE : public Function {
public:
  double operator()() const override { return M_PI; }
  std::string getName() const override { return "pi"; }
  std::string getDescription() const override { return "= 3.14159..."; };

  size_t getnArgs() const override { return 0; }
  void setArg(size_t narg, double arg) override {}
};

extern "C" __declspec(dllexport)
Operator * create() {
  return new NumE();
}