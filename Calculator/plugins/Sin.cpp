#include "../Operators/Operator.h"
#include <cmath>
#define M_PI 3.141592653589793

class Sin : public Operator {
public:
  double operator()() const override { return std::sin(args[0] / 180.0 * M_PI); }
  EPriority getPriority() const override { return EPriority::P_FUNCTION; }
  std::string getName() const override { return "sin"; }

  bool isFunction() const override { return true; }
  size_t getnArgs() const override { return 1; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[1] = { 0 };
};

extern "C" __declspec(dllexport) Operator * create() {
  return new Sin();
}