#include <cmath>
#include "../Operators/Operator.h"

class Pow : public Operator {
public:
  double operator()() const override { return std::pow(args[0], args[1]); }
  EPriority getPriority() const override { return EPriority::P_UPPER; }
  std::string getName() const override { return "^"; }
  
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = { 0 };
};

extern "C" __declspec(dllexport) 
Operator* create() {
  return new Pow();
}