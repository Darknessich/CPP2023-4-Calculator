#include "StandardOps.h"

// ---------------------------- Plus ----------------------------------
double Plus::operator()() const  { return args[0] + args[1]; }
EPriority Plus::getPriority() const  { return EPriority::P_AVERAGE; }
std::string Plus::getName() const  { return "+"; }

bool Plus::isFunction() const  { return false; };
size_t Plus::getnArgs() const  { return 2; }
void Plus::setArg(size_t narg, double arg)  { args[narg] = arg; }

// --------------------------- Minus ----------------------------------
double Minus::operator()() const  { return args[0] - args[1]; }
EPriority Minus::getPriority() const  { return EPriority::P_AVERAGE; }
std::string Minus::getName() const  { return "-"; }

bool Minus::isFunction() const  { return false; };
size_t Minus::getnArgs() const  { return 2; }
void Minus::setArg(size_t narg, double arg)  { args[narg] = arg; }

// -------------------------- Product ---------------------------------
double Product::operator()() const  { return args[0] * args[1]; }
EPriority Product::getPriority() const  { return EPriority::P_HIGH; }
std::string Product::getName() const  { return "*"; }

bool Product::isFunction() const  { return false; };
size_t Product::getnArgs() const  { return 2; }
void Product::setArg(size_t narg, double arg)  { args[narg] = arg; }

// -------------------------- Division --------------------------------
double Division::operator()() const  { return args[0] / args[1]; }
EPriority Division::getPriority() const  { return EPriority::P_HIGH; }
std::string Division::getName() const  { return "/"; }

bool Division::isFunction() const  { return false; };
size_t Division::getnArgs() const  { return 2; }
void Division::setArg(size_t narg, double arg)  { args[narg] = arg; }

std::vector<Operator*> getStandardOps() {
  return { new Plus(), new Minus(), new Product(), new Division() };
}