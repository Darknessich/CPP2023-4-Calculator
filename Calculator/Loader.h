#pragma once
#include <string>
#include "Operators/Operator.h"

class Loader {
public:
  Loader(std::string path);
  Operator* next();

private:
  std::string path;
};