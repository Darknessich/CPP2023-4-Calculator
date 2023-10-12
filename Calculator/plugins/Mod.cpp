#include "../Operators/Operator.h"
#include <cmath>

class Mod : public Operator {
public:
  double operator()() const override { 
    int result = args[0] % args[1];
    return result < 0? args[1] + result : result; 
  }

  EPriority getPriority() const override { return EPriority::P_UPPER; }
  std::string getName() const override { return "mod"; }

  bool isFunction() const override { return false; }
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = static_cast<int>(arg); }
private:
  int args[2] = { 0 };
};

extern "C" __declspec(dllexport) Operator * create() {
  return new Mod();
}