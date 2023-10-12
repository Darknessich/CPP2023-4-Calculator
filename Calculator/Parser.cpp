#include "Parser.h"

using shptrT = std::shared_ptr<Token>;
using VShptrT = std::vector<shptrT>;

void Parser::addName(std::string const& name) {
  this->opNames.insert(name);
  this->sizes.insert(name.size());
}

bool isFloating(char c) {
  return isdigit(c) || c == '.';
}

bool isSign(char c) {
  return (c == '+' || c == '-');
}

bool isBracket(char c) {
  return (c == '(' || c == ')');
}

bool isSeparator(char c) {
  return c == ',';
}

bool Parser::isOpName(std::string const& exp, size_t cnt, std::string& name) const {
  
  for (auto it = this->sizes.rbegin(); it != this->sizes.rend(); it++) {
    if (cnt + *it > exp.size())
      continue;

    name = exp.substr(cnt, *it);
    if (this->opNames.find(name) != this->opNames.end())
      return true;
  }

  name = "";
  return false;
}

std::string getFloating(std::string const& exp, size_t& it) {
  int tmp = 1;
  while (isSign(exp[it]))
    tmp *= (exp[it++] == '+' ? 1 : -1);

  size_t subsize = 0;
  size_t it2 = it;
  while (isFloating(exp[it2])) {
    subsize++;
    it2++;
  }

  std::string ans(((tmp == 1 ? "+" : "-") + exp.substr(it, subsize)));
  it = it2;
  return ans;
}

VShptrT Parser::parse(std::string const& exp) const {
  size_t cnt = 0;
  std::string op;
  bool prevop = true;
  VShptrT tokens;

  while (cnt < exp.size()) {
    if (isspace(exp[cnt])) {
      cnt++;
    }
    else if (isFloating(exp[cnt]) || (prevop && isSign(exp[cnt]))) {
      prevop = false;
      tokens.emplace_back(new Token{Token::EType::T_NUMBER, getFloating(exp, cnt)});
    }
    else if (isBracket(exp[cnt])) {
      prevop = exp[cnt] == '(';
      tokens.emplace_back(new Token{ Token::EType::T_BRACKET, exp.substr(cnt++, 1)});
    }
    else if (isSeparator(exp[cnt])) {
      prevop = true;
      tokens.emplace_back(new Token{ Token::EType::T_SEPARATOR, exp.substr(cnt++, 1) });
    }
    else if (isOpName(exp, cnt, op)){
      prevop = true;
      cnt += op.size();
      tokens.emplace_back(new Token{ Token::EType::T_OPERATOR, op}); 
    }
    else {
      tokens.emplace_back(new Token{ Token::EType::T_NONE, exp.substr(cnt, 1)});
      break;
    }
  }

  return tokens;
}