#include "Flipper.h"
#include "Solver.h"
#include "../Operators/Operator.h"

Flipper::Flipper(Solver* parent)
  : solver(parent)
{}

bool PriorityCompare(EPriority low, EPriority high) {
  return static_cast<int>(low) >= static_cast<int>(high);
}

bool Flipper::isHigherPriority(shToken const& low, shToken const& high) const {
  auto opLow = this->solver->getOperator(low->name);
  auto opHigh = this->solver->getOperator(high->name);

  return opLow && opHigh && PriorityCompare(opLow->getPriority(), opHigh->getPriority());
}

bool Flipper::flipNone(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  msg = "Flipper: Unknown token : \'" + tokens[idx]->name + "\'";
  return false;
}

bool Flipper::flipNumber(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  this->state.out.push_back(tokens[idx]);
  return true;
}

bool Flipper::flipOperator(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  auto& st = this->state.stack;
  while (!st.empty() && this->isHigherPriority(tokens[idx], st.top())) {
    this->state.out.push_back(st.top());
    st.pop();
  }

  st.push(tokens[idx]);
  return true;
}

bool Flipper::flipFunction(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  this->state.stack.push(tokens[idx]);
  return true;
}

bool Flipper::flipSeparator(Tokens const& tokens, std::string& msg) {
  using Type = Token::EType;

  size_t idx = this->state.idx++;
  auto& st = this->state.stack;
  while (!st.empty() && st.top()->type != Type::T_LEFT_BRACKET) {
    this->state.out.push_back(st.top());
    st.pop();
  }

  if (!st.empty() && st.top()->type == Type::T_LEFT_BRACKET)
    return true;

  msg = "Flipper: Opening bracket not found (for function args)";
  return false;
}

bool Flipper::flipLeftBracket(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  this->state.stack.push(tokens[idx]);
  return true;
}

bool Flipper::flipRightBracket(Tokens const& tokens, std::string& msg) {
  using Type = Token::EType;

  size_t idx = this->state.idx++;
  auto& st = this->state.stack;
  while (!st.empty() && st.top()->type != Type::T_LEFT_BRACKET) {
    this->state.out.push_back(st.top());
    st.pop();
  }

  if (st.empty()) {
    msg = "Flipper: Opening bracket not found";
    return false;
  }
  st.pop();
  
  if (!st.empty() && st.top()->type == Type::T_FUNCTION) {
    this->state.out.push_back(st.top());
    st.pop();
  }
  return true;
}

bool Flipper::flipToken(Tokens const& tokens, std::string& msg) {
  using Type = Token::EType;
  switch (tokens[this->state.idx]->type) {
  case Type::T_NONE:
    return this->flipNone(tokens, msg);
  case Type::T_NUMBER:
    return this->flipNumber(tokens, msg);
  case Type::T_OPERATOR:
    return this->flipOperator(tokens, msg);
  case Type::T_FUNCTION:
    return this->flipFunction(tokens, msg);
  case Type::T_SEPARATOR:
    return this->flipSeparator(tokens, msg);
  case Type::T_LEFT_BRACKET:
    return this->flipLeftBracket(tokens, msg);
  case Type::T_RIGHT_BRACKET:
    return this->flipRightBracket(tokens, msg);
  }

  msg = "Flipper: Unknown error";
  return false;
}

bool Flipper::flipState(Tokens& tokens, std::string& msg) {
  using Type = Token::EType;

  auto& st = this->state.stack;
  while (!st.empty()) {
    if (st.top()->type == Type::T_LEFT_BRACKET) {
      msg = "Flipper: Closing bracket not found";
      return false;
    }

    this->state.out.push_back(st.top());
    st.pop();
  }

  tokens = std::move(this->state.out);
  msg = "Flipper: Success";
  return true;
}

bool Flipper::flip(Tokens& tokens, std::string& msg) {
  this->state = State();
  
  while (this->state.idx < tokens.size()) {
    if (!this->flipToken(tokens, msg))
      return false;
  }
  
  return this->flipState(tokens, msg);
}