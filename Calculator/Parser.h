#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <set>

struct Token {
  enum class EType {
    T_NONE,
    T_NUMBER,
    T_OPERATOR,
    T_BRACKET,
    T_SEPARATOR
  } type = EType::T_NONE;
  std::string str;
};

class Parser {
  bool isOpName(std::string const& exp, size_t it, std::string& name) const;

public:
  void addName(std::string const& opName);
  std::vector<Token*> parse(std::string const& exp) const;
private:
  std::unordered_set<std::string> opNames;
  std::set<size_t> sizes;
};