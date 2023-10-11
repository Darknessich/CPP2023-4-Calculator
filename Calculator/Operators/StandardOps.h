#pragma once
#include <vector>

#include "Operator.h"

class Plus : public Operator {
public:
  double operator()() const override { return args[0] + args[1]; }
  EPriority getPriority() const override { return EPriority::P_AVERAGE; }
  std::string getName() const override { return "+"; }
  
  bool isFunction() const override { return false; };
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = { 0 };
};

class Minus : public Operator {
public:
  double operator()() const override { return args[0] - args[1]; }
  EPriority getPriority() const override { return EPriority::P_AVERAGE; }
  std::string getName() const override { return "-"; }

  bool isFunction() const override { return false; };
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = { 0 };
};

class Product : public Operator {
public:
  double operator()() const override { return args[0] * args[1]; }
  EPriority getPriority() const override { return EPriority::P_HIGH; }
  std::string getName() const override { return "*"; }

  bool isFunction() const override { return false; };
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = {0};
};

class Division : public Operator {
public:
  double operator()() const override { return args[0] / args[1]; }
  EPriority getPriority() const override { return EPriority::P_HIGH; }
  std::string getName() const override { return "/"; }

  bool isFunction() const override { return false; };
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = { 0 };
};

std::vector<Operator*> getStandardOps() {
  return { new Plus(), new Minus(), new Product(), new Division() };
}