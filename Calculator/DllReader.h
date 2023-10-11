#pragma once
#include <string>
#include "Operators/Operator.h"

class DllReader {
public:
  DllReader(std::string path);
  Operator* operator()();

private:
  std::string path;
};