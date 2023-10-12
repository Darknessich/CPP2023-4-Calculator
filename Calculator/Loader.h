#pragma once
#include <string>
#include <memory>
#include <windows.h>
#include <exception>

#include "Operators/Operator.h"

class LoaderErr : public std::exception {
public:
  using std::exception::exception;
};

class Loader {
public:
  Loader(std::string const& path);
  ~Loader() noexcept;

  std::shared_ptr<Operator> get() const noexcept;
  std::shared_ptr<Operator> next();
private:
  std::string path;
  WIN32_FIND_DATAA winfd;
  HANDLE hfind;
  std::shared_ptr<Operator> curr;
};