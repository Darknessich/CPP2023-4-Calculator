#include "Solver.h"
#include "Loader.h"
#include "Operators/StandardOps.h"

using shptrT = std::shared_ptr<Token>;
using VShptrT = std::vector<shptrT>;

Solver::Solver() {
  for (auto op : getStandardOps()) {
    this->operators[op->getName()] = std::shared_ptr<Operator>(op);
    this->parser.addName(op->getName());
  }
}

size_t Solver::loadPlugins(std::string path) {
  Loader loader(path);
  size_t cnt = 0;

  for (auto op = loader.get(); op != nullptr; op = loader.next(), cnt++) {
    this->operators[op->getName()] = op;
    this->parser.addName(op->getName());
  }

  return cnt;
}

VShptrT Solver::reverseExpression(VShptrT const& tokens) {
  VShptrT reverseTokens;
  std::stack<shptrT> st;

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
        while (!st.empty() && !isBracket(st.top().get())) {
          reverseTokens.push_back(st.top());
          st.pop();
        }

        if (st.empty())
          throw SolverErr("No opening bracket found");

        st.pop();
        if (!st.empty() && isFunc(st.top().get())) {
          reverseTokens.push_back(st.top());
          st.pop();
        }
      }
      break;

    case Token::EType::T_SEPARATOR:
      while (!st.empty() && !isBracket(st.top().get())) {
        reverseTokens.push_back(st.top());
        st.pop();
      }

      if (st.empty()) 
        throw SolverErr("No opening bracket found (for function args)");
      break;

    case Token::EType::T_OPERATOR:
      if (isFunc(lex.get())) {
        st.push(lex);
        break;
      }

      while (!st.empty() && isOp(st.top().get()) && !isFunc(st.top().get()) && !higherPriority(lex.get(), st.top().get())) {
        reverseTokens.push_back(st.top());
        st.pop();
      }
      st.push(lex);
      break;

    default:
      throw SolverErr(("unknown token: \"" + lex->str + "\"").c_str());
      break;
    }
  }

  while (!st.empty()) {
    if (isBracket(st.top().get()))
      throw SolverErr("No closing bracket found");

    reverseTokens.push_back(st.top());
    st.pop();
  }

  return reverseTokens;
}

void Solver::clearStack() {
  while (!this->values.empty())
    this->values.pop();
}

double Solver::calculate(std::string const& exp) {
  this->tokens = reverseExpression(parser.parse(exp));
  
  for (auto lex : tokens) {
    if (lex->type == Token::EType::T_NUMBER) {
      try {
        this->values.push(std::stod(lex->str));
      }
      catch (...) {
        this->clearStack();
        throw SolverErr(("Expected number, but found \"" + lex->str + "\"").c_str());
      }
    }
    else {
      std::shared_ptr<Operator> op = operators[lex->str];
      for (int i = static_cast<int>(op->getnArgs()) - 1; i >= 0 ; i--) {
        if (this->values.empty())
          throw SolverErr("Too few operands");

        op->setArg(i, values.top());
        this->values.pop();
      }
      this->values.push((*op)());
    }
  }

  if (this->values.empty())
    throw SolverErr("Empty");

  double ans = this->values.top();
  this->values.pop();

  if (!this->values.empty()) {
    this->clearStack();
    throw SolverErr("Too many operands");
  }

  return ans;
}