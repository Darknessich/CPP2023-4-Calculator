#include "Validator.h"
#include "Solver.h"
#include "../Operators/Operator.h"

Validator::Validator(Solver* parent)
  : solver(parent)
{}

size_t Max(size_t a, size_t b) {
  return a > b ? a : b;
}

bool Validator::isLeftOperand(shToken const& token) const {
  using Type = Token::EType;
  bool isPostfix = false;

  if (token->type == Type::T_OPERATOR) {
    auto op = this->solver->getOperator(token->name);
    isPostfix = op ? (op->getFormat() == EFormat::F_POSTFIX) : false;
  }

  return isPostfix || token->type == Type::T_RIGHT_BRACKET || token->type == Type::T_NUMBER;
}

bool Validator::isRightOperand(shToken const& token) const {
  using Type = Token::EType;
  bool isPrefix = false;

  if (token->type == Type::T_OPERATOR) {
    auto op = this->solver->getOperator(token->name);
    isPrefix = op ? (op->getFormat() == EFormat::F_PREFIX) : false;
  }

  return isPrefix || token->type == Type::T_LEFT_BRACKET ||
    token->type == Type::T_NUMBER || token->type == Type::T_FUNCTION;
}

bool Validator::isBeforeRightBracket(shToken const& token) const {
  using Type = Token::EType;
  return this->isLeftOperand(token) ||
    (this->state.inFunction && token->type == Type::T_LEFT_BRACKET);
}

bool Validator::validateNone(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  msg = "Validator: Unknown token : \'" + tokens[idx]->name + "\'";
  return false;
}

bool Validator::validateNumber(Tokens const& tokens, std::string& msg) {
  this->state.func.args = Max(this->state.func.args, 1);
  size_t idx = this->state.idx++;
  if (idx == 0 || !this->isLeftOperand(tokens[idx - 1]))
    return true;

  msg = "Validator: Operator expected but number \'" + tokens[idx]->name + "\' found";
  return false;
}

bool Validator::validateOperator(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  auto op = this->solver->getOperator(tokens[idx]->name);

  if (op == nullptr) {
    msg = "Validator: Operator not found \'" + tokens[idx]->name + "\'";
    return false;
  }

  EFormat fmt = op->getFormat();
  bool leftOperand = idx != 0 && isLeftOperand(tokens[idx - 1]);
  bool rightOperand = idx != tokens.size() - 1 && isRightOperand(tokens[idx + 1]);

  if (fmt == EFormat::F_PREFIX && rightOperand)
    return true;

  if (fmt == EFormat::F_INFIX && rightOperand && leftOperand)
    return true;

  if (fmt == EFormat::F_POSTFIX && leftOperand)
    return true;

  msg = "Validator: Operand not found for operator \'" + tokens[idx]->name + "\'";
  return false;
}

bool Validator::validateFunction(Tokens const& tokens, std::string& msg) {
  using Type = Token::EType;

  size_t idx = this->state.idx++;

  if (this->state.inFunction) {
    this->state.func.args = Max(this->state.func.args, 1);
    this->state.st.push(this->state.func);
  }

  this->state.inFunction = true;
  this->state.func = State::FunctionInfo{ idx, 0, 0 };

  if (idx == tokens.size() - 1 || tokens[idx + 1]->type != Type::T_LEFT_BRACKET) {
    msg = "Validator: Expected opening brackets for function \'" + tokens[idx]->name + "\'";
    return false;
  }

  if (idx == 0 || !this->isLeftOperand(tokens[idx - 1]))
    return true;

  msg = "Validator: Operator expected but function \'" + tokens[idx]->name + "\' found";
  return false;
}

bool Validator::validateSeparator(Tokens const& tokens, std::string& msg) {
  this->state.func.args++;
  size_t idx = this->state.idx++;

  if (!this->state.inFunction) {
    msg = "Validator: Separator found outside function";
    return false;
  }

  bool leftOperand = idx != 0 && isLeftOperand(tokens[idx - 1]);
  bool rightOperand = idx != tokens.size() - 1 && isRightOperand(tokens[idx + 1]);

  if (leftOperand && rightOperand)
    return true;

  msg = "Validator: Argument not found for separator \'" + tokens[idx]->name + "\'";
  return false;
}

bool Validator::validateLeftBracket(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  this->state.brackets++;
  if (this->state.inFunction)
    this->state.func.brackets++;

  if (idx == 0 || !this->isLeftOperand(tokens[idx - 1]))
    return true;

  msg = "Validator: Operator expected but bracket \'" + tokens[idx]->name + "\' found";
  return false;
}

bool Validator::validateFunctionArgs(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.func.fidx;

  auto func = this->solver->getOperator(tokens[idx]->name);

  if (func == nullptr) {
    msg = "Validator: Function not found \'" + tokens[idx]->name + "\'";
    return false;
  }

  if (func->getnArgs() == this->state.func.args)
    return true;

  msg = "Validator: Function \'" + tokens[idx]->name +
    "\' takes " + std::to_string(func->getnArgs()) +
    " arguments rather than " + std::to_string(this->state.func.args);
  return false;
}

bool Validator::validateRightBracket(Tokens const& tokens, std::string& msg) {
  size_t idx = this->state.idx++;
  this->state.brackets--;

  if (idx == 0 || !isBeforeRightBracket(tokens[idx - 1])) {
    msg = "Validator: Operand expected but bracket \'" + tokens[idx]->name + "\' found";
    return false;
  }

  if (!this->state.inFunction || (--this->state.func.brackets != 0))
    return true;

  if (!this->validateFunctionArgs(tokens, msg))
    return false;

  this->state.inFunction = !this->state.st.empty();
  if (this->state.inFunction) {
    this->state.func = this->state.st.top();
    this->state.st.pop();
  }
  return true;
}

bool Validator::validateToken(Tokens const& tokens, std::string& msg) {
  using Type = Token::EType;
  switch (tokens[this->state.idx]->type) {
  case Type::T_NONE:
    return this->validateNone(tokens, msg);
  case Type::T_NUMBER:
    return this->validateNumber(tokens, msg);
  case Type::T_OPERATOR:
    return this->validateOperator(tokens, msg);
  case Type::T_FUNCTION:
    return this->validateFunction(tokens, msg);
  case Type::T_SEPARATOR:
    return this->validateSeparator(tokens, msg);
  case Type::T_LEFT_BRACKET:
    return this->validateLeftBracket(tokens, msg);
  case Type::T_RIGHT_BRACKET:
    return this->validateRightBracket(tokens, msg);
  }

  msg = "Validator: Unknown error";
  return false;
}

bool Validator::validateState(Tokens const& tokens, std::string& msg) {
  if (this->state.inFunction) {
    msg = "Validator: Closing bracket of the function \'" + tokens[this->state.func.fidx]->name + "\' not found";
    return false;
  }

  if (this->state.brackets != 0) {
    msg = "Validator: " + std::to_string(std::abs(this->state.brackets)) +
      (this->state.brackets > 0 ? " closing " : " opening ") +
      "brackets not found!";
    return false;
  }

  msg = "Validator: Success";
  return true;
}

bool Validator::validate(Tokens const& tokens, std::string& msg) {
  this->state = State();

  while (this->state.idx < tokens.size()) {
    if (!this->validateToken(tokens, msg))
      return false;
  }

  return this->validateState(tokens, msg);
}