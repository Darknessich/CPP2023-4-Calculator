#pragma once
#include <memory>
#include <string>
#include <stack>

#include "Parser.h"
class Solver;

class Flipper {
  using shToken = std::shared_ptr<Token>;
  using Tokens = std::vector<shToken>;

  struct State {
    size_t idx = 0;   ///< current token number
    Tokens out;
    std::stack<shToken> stack;
  };

  bool Flipper::isHigherPriority(shToken const& low, shToken const& high) const;

  bool flipNone(Tokens const& tokens, std::string& msg);
  bool flipNumber(Tokens const& tokens, std::string& msg);
  bool flipOperator(Tokens const& tokens, std::string& msg);
  bool flipFunction(Tokens const& tokens, std::string& msg);
  bool flipSeparator(Tokens const& tokens, std::string& msg);
  bool flipLeftBracket(Tokens const& tokens, std::string& msg);
  bool flipRightBracket(Tokens const& tokens, std::string& msg);

  bool flipToken(Tokens const& tokens, std::string& msg);
  bool flipState(Tokens& tokens, std::string& msg);

public:
  Flipper(Solver* parent);
  bool flip(Tokens& tokens, std::string& msg);

private:
  Solver* solver;
  State state;
};
