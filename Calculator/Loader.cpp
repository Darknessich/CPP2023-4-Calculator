#include "Loader.h"

std::shared_ptr<Operator> getOp(std::string const& path) {
  HMODULE hm = LoadLibraryA(path.c_str());

  if (hm == nullptr)
    throw LoaderErr(("File \"" + path + "\" not found").c_str());

  Operator* (*create)() = reinterpret_cast<Operator*(*)()>(GetProcAddress(hm, "create"));

  if (!create) 
    throw LoaderErr(("Òo instance of the function \"Operator* create(void)\" in \"" + path + "\"").c_str());

  return std::shared_ptr<Operator>(create());
}

Loader::Loader(std::string const& path)
  : path(path), curr(nullptr)
{
  this->hfind = FindFirstFileA((this->path + std::string("\\*.dll")).c_str(), &winfd);
  this->curr = (hfind == INVALID_HANDLE_VALUE ? nullptr : getOp(this->path + "\\" + winfd.cFileName));
}

Loader::~Loader() noexcept {
  FindClose(hfind);
}

std::shared_ptr<Operator> Loader::get() const noexcept {
  return curr;
}

std::shared_ptr<Operator> Loader::next() {
  if (!curr || FindNextFileA(hfind, &winfd) == NULL)
    curr = nullptr;
  else {
    this->curr = getOp(this->path + "\\" + winfd.cFileName);
  }

  return curr;
}