#include "Loader.h"

Operator* getOp(std::string const& path) {
  HMODULE hm = LoadLibraryA(path.c_str());

  if (hm == nullptr) {
    // Error
    return nullptr;
  }

  Operator* (*create)() = reinterpret_cast<Operator*(*)()>(GetProcAddress(hm, "create"));

  if (!create) {
    //Error
    return nullptr;
  }

  return create();
}

Loader::Loader(std::string const& path)
  : path(path), curr(nullptr)
{
  this->hfind = FindFirstFileA((this->path + std::string("/*.dll")).c_str(), &winfd);
  this->curr = getOp(this->path + "/" + winfd.cFileName);
}

Loader::~Loader() {
  FindClose(hfind);
}

Operator* Loader::get() const {
  return curr;
}

Operator* Loader::next() {
  if (!curr || FindNextFileA(hfind, &winfd) == NULL)
    curr = nullptr;
  else {
    this->curr = getOp(this->path + "/" + winfd.cFileName);
  }

  return curr;
}