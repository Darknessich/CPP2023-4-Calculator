#define _USE_MATH_DEFINES
#include <cmath>

#include "../Operators/Operator.h"

class Sin : public Function {
public:
  double operator()() const override { return std::sin((args[0] * M_PI) / 180.0); }
  std::string getName() const override { return "sin"; }
  std::string getDescription() const override { return "sin(deg)"; };

  size_t getnArgs() const override { return 1; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[1] = { 0 };
};

extern "C" __declspec(dllexport) 
Operator * create() {
  return new Sin();
}