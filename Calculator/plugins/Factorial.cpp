#include "../Operators/Operator.h"
#include <limits>

class Factorial : public Operator {
public:
  double operator()() const override {
    if (args[0] < 0)
      return -std::numeric_limits<double>::infinity();
    if (args[0] > 170)
      return std::numeric_limits<double>::infinity();

    double result = 1;
    for (int i = 2; i <= args[0]; i++)
      result *= i;
    return result;
  }

  EPriority getPriority() const override { return EPriority::P_UPPER; }
  EFormat getFormat() const override { return EFormat::F_POSTFIX; }
  std::string getName() const override { return "!"; }
  std::string getDescription() const override { return "int(n)!"; }
  size_t getnArgs() const override { return 1; }

  void setArg(size_t narg, double arg) override { args[narg] = static_cast<int>(arg); }
private:
  int args[1] = { 0 };
};

extern "C" __declspec(dllexport)
Operator * create() {
  return new Factorial();
}