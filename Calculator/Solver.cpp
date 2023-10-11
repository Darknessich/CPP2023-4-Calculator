#include "Solver.h"
#include "Loader.h"
#include "Operators/StandardOps.h"

class Sin2 : public Operator {
public:
  double operator()() const override { return args[0] * args[1]; }
  EPriority getPriority() const override { return EPriority::P_AVERAGE; }
  std::string getName() const override { return "sin2"; }

  bool isFunction() const override { return true; };
  size_t getnArgs() const override { return 2; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[2] = { 0 };
};

Solver::Solver() {
  for (auto op : getStandardOps()) {
    this->operators[op->getName()] = op;
    this->parser.addName(op->getName());
  }

  this->operators["sin2"] = new Sin2();
  this->parser.addName("sin2");
}

size_t Solver::loadPlugins(std::string path) {
  Loader loader(path);
  size_t cnt = 0;

  for (Operator* op = loader.get(); op != nullptr; op = loader.next(), cnt++) {
    this->operators[op->getName()] = op;
    this->parser.addName(op->getName());
  }

  return cnt;
}

std::vector<Token*> Solver::reverseExpression(std::vector<Token*> const& tokens) {
  std::vector<Token*> reverseTokens;
  std::stack<Token*> st;

  auto isBracket = [](Token* tk) -> bool {
    return tk->type == Token::EType::T_BRACKET;
  };

  auto isOp = [](Token* tk) -> bool {
    return tk->type == Token::EType::T_OPERATOR;
  };

  auto isFunc = [this, &isOp](Token* tk) -> bool {
    return isOp(tk) && this->operators[tk->str]->isFunction();
  };

  auto higherPriority = [this](Token* left, Token* right) -> bool {
    return static_cast<int>(operators[left->str]->getPriority()) <
      static_cast<int>(operators[right->str]->getPriority());
  };

  for (auto lex : tokens) {
    switch (lex->type) {

    case Token::EType::T_NUMBER:
      reverseTokens.push_back(lex);
      break;

    case Token::EType::T_BRACKET:
      if (lex->str == "(")
        st.push(lex);
      else {
        while (!st.empty() && !isBracket(st.top())) {
          reverseTokens.push_back(st.top());
          st.pop();
        }

        if (st.empty()) {
          // Error
          return {};
        }
        st.pop();
        if (!st.empty() && isFunc(st.top())) {
          reverseTokens.push_back(st.top());
          st.pop();
        }
      }
      break;

    case Token::EType::T_SEPARATOR:
      while (!st.empty() && !isBracket(st.top())) {
        reverseTokens.push_back(st.top());
        st.pop();
      }

      if (st.empty()) {
        // Error
        return {};
      }

      break;

    case Token::EType::T_OPERATOR:
      if (isFunc(lex)) {
        st.push(lex);
        break;
      }

      while (!st.empty() && isOp(st.top()) && !higherPriority(lex, st.top())) {
        reverseTokens.push_back(st.top());
        st.pop();
      }
      st.push(lex);
      break;

    default:
      // Error
      return {};
      break;
    }
  }

  while (!st.empty()) {
    if (isBracket(st.top())) {
      // Error
      return {};
    }
    reverseTokens.push_back(st.top());
    st.pop();
  }

  return reverseTokens;
}

double Solver::calculate(std::string const& exp) {
  this->tokens = reverseExpression(parser.parse(exp));

  for (auto lex : tokens) {
    if (lex->type == Token::EType::T_NUMBER)
      values.push(std::stod(lex->str));
    else {
      Operator* op = operators[lex->str];
      for (int i = op->getnArgs() - 1; i >= 0 ; i--) {
        if (values.empty()) {
          // Error
          return 0.0;
        }
        
        op->setArg(i, values.top());
        values.pop();
      }
      values.push((*op)());
    }
  }

  double ans = values.top();
  values.pop();

  if (!values.empty()) {
    // Error
    return 0.0;
  }

  return ans;
}