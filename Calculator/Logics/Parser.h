#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <set>

struct Token {
  enum class EType {
    T_NONE,
    T_NUMBER,
    T_OPERATOR,
    T_FUNCTION,
    T_SEPARATOR,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
  };
  
  EType type;
  std::string name;

  Token(EType type = EType::T_NONE, std::string name = "");
};

class Parser {
  using shToken = std::shared_ptr<Token>;

  struct State {
    bool beSigned = true;   ///< can + or -be a sign?
    size_t idx = 0;         ///< current token number
  };
  
  bool isNumber(std::string const& exp) const;
  bool isOperator(std::string const& exp, std::string& name) const;
  bool isFunction(std::string const& name) const;
  
  shToken getSpace();
  shToken getNumber(std::string const& exp);
  shToken getLeftBracket();
  shToken getRightBracket();
  shToken getSeparator();
  shToken getOperator(std::string const& name);
  shToken getToken(std::string const& exp);

public:
  Parser();
  void addOperator(std::string const& name, bool isFunction);
  std::vector<shToken> parse(std::string const& exp);

private:
  std::unordered_set<std::string> operators;
  std::unordered_set<std::string> functions;
  std::set<size_t> sizes;
  std::unique_ptr<State> state;
};