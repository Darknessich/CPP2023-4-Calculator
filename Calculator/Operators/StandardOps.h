#pragma once
#include <vector>
#include <memory>

#include "Operator.h"

std::vector<std::unique_ptr<Operator>> getStandardOps();

class Plus : public Operator {
public:
  double operator()() const override;
  std::string getName() const override;
  EPriority getPriority() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};

class Minus : public Operator {
public:
  double operator()() const override;
  std::string getName() const override;
  EPriority getPriority() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};

class Product : public Operator {
public:
  double operator()() const override;
  std::string getName() const override;
  EPriority getPriority() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};

class Division : public Operator {
public:
  double operator()() const override;
  std::string getName() const override;
  EPriority getPriority() const override;
  void setArg(size_t narg, double arg) override;
private:
  double args[2] = { 0 };
};