#pragma once
#include <string>

enum class EPriority {
  P_FUNCTION, //< for functions
  P_UPPER,
  P_HIGH,
  P_AVERAGE,
  P_LOW,
  P_LOWEST
};

enum class EFormat {
  F_PREFIX,   //< for operators with 1 arg and functions
  F_INFIX,    //< for standard operators
  F_POSTFIX   //< for operators with 1 arg
};

class Operator {
public:
  virtual double operator()() const = 0;
  
  virtual std::string getName() const = 0;
  virtual EPriority getPriority() const = 0;
  virtual void setArg(size_t narg, double arg) = 0;
  
  virtual ~Operator() = default;

  virtual size_t getnArgs() const { return 2; };
  virtual EFormat getFormat() const { return EFormat::F_INFIX; }
  bool isFunction() const { return this->getPriority() == EPriority::P_FUNCTION; };
};

class Function : public Operator {
public:
  EFormat getFormat() const override final { return EFormat::F_PREFIX; };
  EPriority getPriority() const override final { return EPriority::P_FUNCTION; };
  size_t getnArgs() const override = 0;
};