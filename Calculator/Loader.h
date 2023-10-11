#pragma once
#include <string>
#include "Operators/Operator.h"

class Loader {
public:
  Loader(std::string const& path);

  Operator* get() const;
  Operator* next();

private:
  std::string path;
};