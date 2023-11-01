#pragma once
#include <memory>
#include <string>
#include <stack>

#include "Parser.h"
class Solver;

class Validator {
  using shToken = std::shared_ptr<Token>;
  using Tokens = std::vector<shToken>;

  struct State {
    struct FunctionInfo {
      size_t fidx = 0;      ///< number of token function
      size_t args = 0;      ///< number of curr argument
      int brackets = 0;     ///< number of unclosed brackets in function
    };

    size_t idx = 0;             ///< current token number
    int brackets;               ///< number of unclosed brackets
    bool inFunction = false;    ///< indicator: are we inside a function?
    FunctionInfo func;          ///< info of current function
    std::stack<FunctionInfo> st;///< stack of called functions
  };

  bool isLeftOperand(shToken const& token) const;
  bool isRightOperand(shToken const& token) const;
  bool isBeforeRightBracket(shToken const& token) const;

  bool validateNone(Tokens const& tokens, std::string& msg);
  bool validateNumber(Tokens const& tokens, std::string& msg);
  bool validateOperator(Tokens const& tokens, std::string& msg);
  bool validateFunction(Tokens const& tokens, std::string& msg);
  bool validateSeparator(Tokens const& tokens, std::string& msg);
  bool validateLeftBracket(Tokens const& tokens, std::string& msg);
  bool validateFunctionArgs(Tokens const& tokens, std::string& msg);
  bool validateRightBracket(Tokens const& tokens, std::string& msg);

  bool validateToken(Tokens const& tokens, std::string& msg);
  bool validateState(Tokens const& tokens, std::string& msg);

public:
  Validator(Solver* parent);
  bool validate(Tokens const& tokens, std::string& msg);

private:
  Solver* const solver;
  std::unique_ptr<State> state;
};