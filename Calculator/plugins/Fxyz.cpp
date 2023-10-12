#include "../Operators/Operator.h"
#include <cmath>

class Fxyz : public Operator {
public:
  // x^3 - y^2 + z
  double operator()() const override { return args[0] * args[0] * args[0] - args[1] * args[1] + args[2]; }
  EPriority getPriority() const override { return EPriority::P_FUNCTION; }
  std::string getName() const override { return "fxyz"; }

  bool isFunction() const override { return true; }
  size_t getnArgs() const override { return 3; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[3] = { 0 };
};

extern "C" __declspec(dllexport) Operator * create() {
  return new Fxyz();
}