#ifndef ELEMENT_H
#define ELEMENT_H

#include <math.h>

#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

#define NUM_GRID_AUTO 8
#define NUM_GRID_MAX 26
#define SCALE_COEF 40.0
#define MOVE_COEF 127.0
#define COMPRESS_COEF 15.0

namespace s21 {

class Element;
class Errors;
class ModelCalc;
class Model;

enum enumElement : uint8_t {
  T,
  plus,
  minus,
  div,
  mult,
  close,
  mod,
  power,
  open,
  msin,
  mcos,
  tg,
  masin,
  macos,
  atg,
  msqrt,
  ln,
  mlog,
  uplus,
  uminus,
  number,
  p,
  e,
  x,
  inf
};

struct point_pair {
  bool flag;
  double x;
  double y;
  double xval;
  double yval;
  point_pair(bool f, int xi, int yi, double xv, double yv)
      : flag(f), x(xi), y(yi), xval(xv), yval(yv) {}
  point_pair(bool f) : flag(f), x(0), y(0), xval(0), yval(0) {}
};

struct ctrl_point {
  int yp;
  double yval;
  double xval;
};

typedef std::vector<point_pair> point_vec;
typedef std::pair<double, int> grid_pair;
typedef std::vector<grid_pair> grid_vec;
typedef std::pair<std::string, std::string> error_pair;
typedef std::pair<std::string, Element> name_pair;

class Errors {
 private:
  error_pair errorPair;
  std::string errorPlace;

 public:
  Errors() : errorPair(error_pair("begin", "begin")) {}
  void addString(std::string const &str);
  void throwError();
  void clear();
  void setPlace(std::string const &place) { errorPlace = place; }
  void throwError(std::string const &er);
};

class Element {
 private:
  enumElement op;

 public:
  Element() : op(T) {}
  Element(enumElement O) : op(O) {}
  int operatorPrice() const;
  bool checkLast(Element &oper, Errors &er) const;
  bool operator==(enumElement other) const { return op == other; }
  bool operator!=(enumElement other) const { return op != other; }
  bool operator<(enumElement other) const { return op < other; }
  bool operator>(enumElement other) const { return op > other; }
  bool operator>=(enumElement other) const { return op >= other; }
  bool operator<=(enumElement other) const { return op <= other; }
  bool operator>=(Element other) const {
    return operatorPrice() >= other.operatorPrice();
  }
  double count(double a) const;
  double count(double a, double b) const;
};

class Mlist : public std::list<std::pair<Element, double>> {
 public:
  void push_back(double n) { emplace_back(Element(number), n); }
  void push_back(Element o) { emplace_back(o, 0); }
};

}  // namespace s21

#endif
