#include "Solver.h"
#include "Loader.h"
#include "../Operators/StandardOps.h"

#include <iomanip>

Solver::Solver()
  : parser(std::make_unique<Parser>()), 
  validator(std::make_unique<Validator>(this)), 
  flipper(std::make_unique<Flipper>(this))
{
  for (auto&& op : getStandardOps()) {
    this->parser->addOperator(op->getName(), op->isFunction());
    this->operators.insert({ op->getName(), std::move(op) });
  }
}

std::pair<size_t, size_t> Solver::loadPlugins(std::string path) {
  Loader loader(path);
  size_t cnt = 0;
  size_t success = 0;

  for (auto&& op = loader.get(); !loader.isEnd(); op = loader.next(), cnt++) {
    if (op != nullptr) {
      success++;
      this->parser->addOperator(op->getName(), op->isFunction());
      this->operators.insert({ op->getName(), std::move(op) });
    }
  }

  return { success, cnt };
}

Operator* const Solver::getOperator(std::string const& name) const {
  auto op = operators.find(name);
  return op == operators.end() ? nullptr : op->second.get();
}

std::string typeToStr(bool isFunction) {
  return isFunction ? "function" : "operator";
}

std::string formatToStr(EFormat fmt) {
  switch (fmt) {
  case EFormat::F_PREFIX:
    return "prefix";
  case EFormat::F_INFIX:
    return "infix";
  case EFormat::F_POSTFIX:
    return "postfix";
  }
  
  return "";
}

void Solver::printInfo(std::ostream& os) const {
  using namespace std;
  const size_t columnw = 12;
  os << setw(columnw) << left << "Type";
  os << setw(columnw) << left << "Name";
  os << setw(columnw) << left << "Format";
  os << setw(columnw) << left << "cargs";
  os << setw(columnw) << left << "description";
  os << endl;

  for (auto const& [name, op] : this->operators) {
    os << setw(columnw) << left << typeToStr(op->isFunction());
    os << setw(columnw) << left << name;
    os << setw(columnw) << left << formatToStr(op->getFormat());
    os << setw(columnw) << left << std::to_string(op->getnArgs());
    os << setw(columnw) << left << op->getDescription();
    os << endl;
  }

  os << endl;
}

double Solver::calculateToken(shToken const& token, bool& ok, std::string& msg) {
  using Type = Token::EType;
  
  ok = true;
  if (token->type == Type::T_NUMBER)
    return std::stod(token->name);

  auto op = this->getOperator(token->name);
  if (op == nullptr) {
    ok = false;
    msg = "Solver: Operator / Function not found \'" + token->name + "\'";
    return 0.0;
  }

  for (int i = static_cast<int>(op->getnArgs()) - 1; i >= 0; i--) {
    if (this->values.empty()) {
      ok = false;
      msg = "Solver: Too few operands for Operator / Function \'" + token->name + "\'";
      return 0.0;
    }

    op->setArg(i, values.top());
    this->values.pop();
  }
  
  return (*op)();
}

double Solver::calculateState(bool& ok, std::string& msg) {
  if (this->values.empty()) {
    ok = false;
    msg = "Solver: Empty expression";
    return 0.0;
  }

  double result = this->values.top();
  this->values.pop();

  if (!this->values.empty()) {
    ok = false;
    msg = "Solver: Too many operands";
    return 0.0;
  }

  return result;
}

double Solver::calculate(std::string const& exp, bool& ok, std::string& msg) {
  this->values = std::stack<double>();
  this->tokens = parser->parse(exp);

  if (!(ok = validator->validate(this->tokens, msg)))
    return 0.0;

  if (!(ok = flipper->flip(this->tokens, msg)))
    return 0.0;

  for (auto const& token : this->tokens) {
    double val = this->calculateToken(token, ok, msg);
    if (!ok)
      return 0.0;
    this->values.push(val);
  }
  
  return this->calculateState(ok, msg);
}