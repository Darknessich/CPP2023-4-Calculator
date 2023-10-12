#pragma once
#include <vector>

#include "Operator.h"

std::vector<Operator*> getStandardOps();

class Plus : public Operator {
public:
  double operator()() const override;
  EPriority getPriority() const override;
  std::string getName() const override;
  
  bool isFunction() const override;
  size_t getnArgs() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};

class Minus : public Operator {
public:
  double operator()() const override;
  EPriority getPriority() const override;
  std::string getName() const override;

  bool isFunction() const override;
  size_t getnArgs() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};

class Product : public Operator {
public:
  double operator()() const override;
  EPriority getPriority() const override;
  std::string getName() const override;

  bool isFunction() const override;
  size_t getnArgs() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = {0};
};

class Division : public Operator {
public:
  double operator()() const override;
  EPriority getPriority() const override;
  std::string getName() const override;

  bool isFunction() const override;
  size_t getnArgs() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};