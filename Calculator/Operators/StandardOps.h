#pragma once
#include "Operator.h"

class Plus : public Operator {
public:
  double operator()() const override { return args[0] + args[1]; }
  size_t getnArgs() const override { return 2; }
  EPriority getPriority() const override { return EPriority::P_AVERAGE; }
  std::string getName() const override { return "+"; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2];
};

class Minus : public Operator {
public:
  double operator()() const override { return args[0] - args[1]; }
  size_t getnArgs() const override { return 2; }
  EPriority getPriority() const override { return EPriority::P_AVERAGE; }
  std::string getName() const override { return "-"; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2];
};

class Product : public Operator {
public:
  double operator()() const override { return args[0] * args[1]; }
  size_t getnArgs() const override { return 2; }
  EPriority getPriority() const override { return EPriority::P_HIGH; }
  std::string getName() const override { return "*"; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2];
};

class Division : public Operator {
public:
  double operator()() const override { return args[0] / args[1]; }
  size_t getnArgs() const override { return 2; }
  EPriority getPriority() const override { return EPriority::P_HIGH; }
  std::string getName() const override { return "/"; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2];
};