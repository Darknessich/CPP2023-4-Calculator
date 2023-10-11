#pragma once
#include <string>
#include <windows.h>
#include "Operators/Operator.h"


class Loader {
public:
  Loader(std::string const& path);
  ~Loader();

  Operator* get() const;
  Operator* next();
private:
  std::string path;
  WIN32_FIND_DATAA winfd;
  HANDLE hfind;
  Operator* curr;
};