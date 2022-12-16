
#include "model.h"

using namespace s21;

ModelCalc::ModelCalc()
    : xn(0), impasse({Element(T)}), postfix(), last() {
  if (std::stof("0.5") > 0.1)
    decimalPoint = '.';
  else
    decimalPoint = ',';
}

double ModelCalc::result() {
  clear();
  parsing();
  return count();
}

void ModelCalc::clear() {
  postfix.clear();
  impasse = std::stack<Element>({Element(T)});
  last = Element(T);
  er.clear();
}

void ModelCalc::setExpression(std::string &input) {
  expression = input;
  setPlace("main input");
}

void ModelCalc::setX(std::string &x) {
  for (auto c : expression) {
    if (c == 'x') {
      ModelCalc modX;
      xn = modX.countX(x, "x input");
      return;
    }
  }
}

double ModelCalc::countX(std::string &x, std::string place) {
  setPlace(place);
  for (auto c : x)
    if (c == 'x') er.throwError("enter without x");
  expression = x;
  return result();
}

double ModelCalc::count() const {
  std::stack<double> buff;
  for (auto i = postfix.begin(); i != postfix.end(); i++) {
    if (i->first == number) {
      buff.push(i->second);
    } else if (i->first == x) {
      buff.push(xn);
    } else if (i->first < open) {
      double b = buff.top();
      buff.pop();
      buff.top() = i->first.count(buff.top(), b);
    } else {
      buff.top() = i->first.count(buff.top());
    }
  }
  double res = buff.top();
  buff.pop();
  return res;
}

void ModelCalc::parsing() {
  if (expression == "auto") er.throwError("please enter a value");
  for (auto c = expression.begin(); c != expression.end(); c++) {
    *c = std::tolower(*c);
    if (*c == '.' && decimalPoint == ',')
      *c = ',';
    else if (*c == ',' && decimalPoint == '.')
      *c = '.';
  }
  name_pair names[] = {
      {"+", plus},      {"-", minus},   {"*", mult},    {"/", div},
      {"(", open},      {")", close},   {"^", power},   {"sin", msin},
      {"cos", mcos},     {"tan", tg},    {"tg", tg},     {"mod", mod},
      {"sqrt", msqrt},   {"asin", masin}, {"acos", macos}, {"arcsin", masin},
      {"arccos", macos}, {"atan", atg},  {"arctg", atg}, {"arctan", atg},
      {"atg", atg},     {"log", mlog},   {"ln", ln},     {"pi", p},
      {"e", e},         {"x", x},       {"p", p},       {"%", mod},
      {"inf", inf},     {"π", p}};
  for (std::size_t k = 0; k < expression.size();) {
    auto kBuff = k;
    if ((expression)[k] == ' ') {
      ++k;
    } else if (isdigit((expression)[k])) {
      toStack(k);
    } else {
      for (auto for_find : names) {
        if (expression.substr(k, for_find.first.size()) == for_find.first) {
          toStack(for_find, k);
          break;
        }
      }
    }
    if (kBuff == k) er.throwError("Unknown symbol");
  }
  er.addString("in the end");
  toStack(Element(T));
  if (impasse.top() != T) er.throwError("'(' > ')'");
}

void ModelCalc::toStack(std::size_t &k) {
  std::size_t add = 0;
  postfix.push_back(std::stod(&(expression)[k], &add));
  er.addString(expression.substr(k, add));
  if (last >= number || last == close) er.throwError();
  k += add;
  last = number;
}

void ModelCalc::toStack(name_pair np, std::size_t &k) {
  er.addString(np.first);
  k += np.first.size();
  toStack(np.second);
}

void ModelCalc::toStack(Element oper) {
  if (last.checkLast(oper, er)) operatorRoat(mult);
  if (oper == inf)
    postfix.push_back(INFINITY);
  else if (oper == p)
    postfix.push_back(M_PI);
  else if (oper == e)
    postfix.push_back(M_E);
  else if (oper == x)
    postfix.push_back(Element(x));
  else
    operatorRoat(oper);
  last = oper;
}

void ModelCalc::operatorRoat(Element oper) {
  if (oper == close) return closeOper();
  while (impasse.top() >= oper && impasse.top() != open && impasse.top() != T)
    impasToPost();
  if (oper != T) impasse.push(oper);
}

void ModelCalc::closeOper() {
  while (impasse.top() != open) {
    if (impasse.top() == T) er.throwError("')' > '('");
    impasToPost();
  }
  impasse.pop();
}

void ModelCalc::impasToPost() {
  postfix.push_back(impasse.top());
  impasse.pop();
}
