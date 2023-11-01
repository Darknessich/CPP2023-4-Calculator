#include "Parser.h"

using shToken = std::shared_ptr<Token>;
using Tokens = std::vector<shToken>;

Token::Token(EType type, std::string name) 
  : type(type), name(name)
{}

Parser::Parser()
  : state(std::make_unique<Parser::State>())
{}

void Parser::addOperator(std::string const& name, bool isFunction) {
  this->operators.insert(name);
  this->sizes.insert(name.size());
  if (isFunction)
    this->functions.insert(name);
}

bool isFloating(std::string const& exp, size_t idx) {
  return std::isdigit(exp[idx]) || (exp[idx] == '.' && idx < exp.size() - 1 && std::isdigit(exp[idx + 1]));
}

bool isSigned(std::string const& exp, size_t idx) {
  while (exp[idx] == '-' || exp[idx] == '+')
    idx++;
  return isFloating(exp, idx);
}

bool Parser::isNumber(std::string const& exp) const {
  size_t start = this->state->idx;
  bool sign = this->state->beSigned && isSigned(exp, start);
  return sign || isFloating(exp, start);
}

bool Parser::isOperator(std::string const& exp, std::string& name) const {
  for (auto it = this->sizes.rbegin(); it != this->sizes.rend(); it++) {
    if (state->idx + *it > exp.size())
      continue;

    name = exp.substr(state->idx, *it);
    if (this->operators.find(name) != this->operators.end())
      return true;
  }

  name = "";
  return false;
}

bool Parser::isFunction(std::string const& name) const {
  return (this->functions.find(name) != this->functions.end());
}

shToken Parser::getSpace() {
  this->state->idx++;
  return nullptr;
}

shToken Parser::getNumber(std::string const& exp) {
  this->state->beSigned = false;
  
  int sign = 1;
  while (exp[this->state->idx] == '+' || exp[this->state->idx] == '-')
    sign *= (exp[this->state->idx++] == '+'? 1 : -1);

  size_t start = this->state->idx;
  while (std::isdigit(exp[this->state->idx]) || exp[this->state->idx] == '.')
    this->state->idx++;

  std::string num = (sign == 1 ? "+" : "-");
  num += exp.substr(start, state->idx - start);
  num += (num.back() == '.' ? "0" : "");

  return std::make_shared<Token>(Token::EType::T_NUMBER, num);
}

shToken Parser::getLeftBracket() {
  this->state->idx++;
  this->state->beSigned = true;
  return std::make_shared<Token>(Token::EType::T_LEFT_BRACKET, "(");
}

shToken Parser::getRightBracket() {
  this->state->idx++;
  this->state->beSigned = false;
  return std::make_shared<Token>(Token::EType::T_RIGHT_BRACKET, ")");
}

shToken Parser::getSeparator() {
  this->state->idx++;
  this->state->beSigned = true;
  return std::make_shared<Token>(Token::EType::T_SEPARATOR, ",");
}

shToken Parser::getOperator(std::string const& name) {
  using Type = Token::EType;
  
  this->state->idx += name.size();
  this->state->beSigned = true;
  return std::make_shared<Token>(this->isFunction(name)? Type::T_FUNCTION : Type::T_OPERATOR, name);
}

shToken Parser::getToken(std::string const& exp) {
  if (std::isspace(exp[this->state->idx]))
    return this->getSpace();

  if (this->isNumber(exp))
    return this->getNumber(exp);

  if (exp[this->state->idx] == '(')
    return this->getLeftBracket();

  if (exp[this->state->idx] == ')')
    return this->getRightBracket();

  if (exp[this->state->idx] == ',')
    return this->getSeparator();

  std::string name;
  if (this->isOperator(exp, name))
    return this->getOperator(name);

  return std::make_shared<Token>(Token::EType::T_NONE, exp.substr(this->state->idx++, 1));
}

Tokens Parser::parse(std::string const& exp) {
  *this->state = State();
  Tokens tokens;

  while (this->state->idx < exp.size()) {
    shToken token = getToken(exp);
    
    if (token == nullptr)
      continue;

    tokens.push_back(token);
    if (token->type == Token::EType::T_NONE)
      break;
  }

  return tokens;
}