#include "element.h"

using namespace s21;

bool Element::checkLast(Element &oper, Errors &er) const {
  switch (op) {
    case mod:
    case div:
    case mult:
    case minus:
    case plus:
    case uminus:
    case uplus:
    case power:
      if (oper <= power) er.throwError();
      return false;
    case close:
      if (oper == open) {
        return true;
      }
      if (oper > power) er.throwError();
      return false;
    case number:
      if (oper > power) return true;
      return false;
    case x:
    case p:
    case e:
    case inf:
      if (oper == number) er.throwError();
      if (oper > power) return true;
      return false;
    case T:
      if (oper == T) er.throwError("enter an expression");
      if (oper >= div && oper <= power) er.throwError();
      if (oper == minus)
        oper = uminus;
      else if (oper == plus)
        oper = uplus;
      return false;
    case open:
      if (oper == T || (oper < open && oper >= div)) er.throwError();
      if (oper == minus)
        oper = uminus;
      else if (oper == plus)
        oper = uplus;
      return false;
    default:
      if ((oper < open) || (oper > open && oper < number)) er.throwError();
      return false;
  }
}

int Element::operatorPrice() const {
  switch (op) {
    case T:
      return -1;
    case close:
      return 0;
    case plus:
    case minus:
      return 1;
    case div:
    case mult:
    case mod:
      return 2;
    case power:
      return 3;
    case uplus:
    case uminus:
      return 4;
    case open:
      return 6;
    default:
      return 5;
  }
}

double Element::count(double a, double b) const {
  using namespace std;
  switch (op) {
    case plus:
      return a + b;
    case minus:
      return a - b;
    case div:
      return a / b;
    case mult:
      return a * b;
    case mod:
      return fmod(a, b);
    case power:
      return pow(a, b);
    default:
      return 0;
  }
}

double Element::count(double a) const {
  using namespace std;
  switch (op) {
    case msin:
      return sin(a);
    case mcos:
      return cos(a);
    case masin:
      return asin(a);
    case macos:
      return acos(a);
    case tg:
      return tan(a);
    case atg:
      return atan(a);
    case msqrt:
      return sqrt(a);
    case ln:
      return log(a);
    case mlog:
      return log10(a);
    case uplus:
      return a;
    case uminus:
      return 0 - a;
    default:
      return 0;
  }
}

void Errors::addString(std::string const &str) {
  errorPair.first = errorPair.second;
  errorPair.second = str;
}

void Errors::throwError() {
  throw std::runtime_error(errorPlace + ": " + errorPair.first + " " +
                           errorPair.second);
}

void Errors::throwError(std::string const &er) {
  throw std::runtime_error(errorPlace + ": " + er);
}

void Errors::clear() {
  errorPair.first = "begin";
  errorPair.second = "begin";
}
