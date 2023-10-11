#include "../Operators/Operator.h"
#include <cmath>

class Pow : public Operator {
public:
  double operator()() const override { return std::pow(args[0], args[1]); }
  EPriority getPriority() const override { return EPriority::P_UPPER; }
  std::string getName() const override { return "^"; }
  
  bool isFunction() const override { return false; }
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = { 0 };
};

extern "C" __declspec(dllexport) Operator* create() {
  return new Pow();
}