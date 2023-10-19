#include "../Operators/Operator.h"

class Factorial : public Operator {
public:
  double operator()() const override {
    return !args[0];
  }

  EPriority getPriority() const override { return EPriority::P_UPPER; }
  EFormat getFormat() const override { return EFormat::F_PREFIX; }
  std::string getName() const override { return "not"; }
  size_t getnArgs() const override { return 1; }

  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[1] = { 0.0 };
};

extern "C" __declspec(dllexport)
Operator * create() {
  return new Factorial();
}