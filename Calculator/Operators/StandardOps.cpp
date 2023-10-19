#include "StandardOps.h"

// ---------------------------- Plus ----------------------------------
double Plus::operator()() const  { return args[0] + args[1]; }
EPriority Plus::getPriority() const  { return EPriority::P_AVERAGE; }
std::string Plus::getName() const  { return "+"; }
std::string Plus::getDescription() const { return "a + b"; }
void Plus::setArg(size_t narg, double arg)  { args[narg] = arg; }

// --------------------------- Minus ----------------------------------
double Minus::operator()() const  { return args[0] - args[1]; }
EPriority Minus::getPriority() const  { return EPriority::P_AVERAGE; }
std::string Minus::getName() const  { return "-"; }
std::string Minus::getDescription() const { return "a - b"; }
void Minus::setArg(size_t narg, double arg)  { args[narg] = arg; }

// -------------------------- Product ---------------------------------
double Product::operator()() const  { return args[0] * args[1]; }
EPriority Product::getPriority() const  { return EPriority::P_HIGH; }
std::string Product::getName() const  { return "*"; }
std::string Product::getDescription() const { return "a * b"; }
void Product::setArg(size_t narg, double arg)  { args[narg] = arg; }

// -------------------------- Division --------------------------------
double Division::operator()() const  { return args[0] / args[1]; }
EPriority Division::getPriority() const  { return EPriority::P_HIGH; }
std::string Division::getName() const  { return "/"; }
std::string Division::getDescription() const { return "a / b"; }
void Division::setArg(size_t narg, double arg)  { args[narg] = arg; }


std::vector<std::unique_ptr<Operator>> getStandardOps() {
  std::vector<std::unique_ptr<Operator>> operators;
  operators.emplace_back(std::make_unique<Plus>());
  operators.emplace_back(std::make_unique<Minus>());
  operators.emplace_back(std::make_unique<Product>());
  operators.emplace_back(std::make_unique<Division>());
  return operators;
}