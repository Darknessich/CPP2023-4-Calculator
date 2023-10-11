#pragma once
#include <string>

enum class EPriority {
  P_UPPER,
  P_HIGH,
  P_AVERAGE,
  P_LOW,
  P_LOWEST
};

class Operator {
public:
  virtual double operator()() const = 0;
  virtual size_t getnArgs() const = 0;
  virtual EPriority getPriority() const = 0;
  virtual std::string getName() const = 0;
  virtual void setArg(size_t narg, double arg) = 0;
  virtual ~Operator() = default;
};