#ifndef MODEL_H
#define MODEL_H

#include "element.h"

namespace s21 {

class ModelCalc {
 protected:
  double xn;
  double count() const;
  virtual void xError() { return; }
  void parsing();
  void setPlace(std::string place) { er.setPlace(place); }
  void clear();

 private:
  char decimalPoint;
  Errors er;
  std::string expression;
  std::stack<Element> impasse;
  Mlist postfix;
  Element last;
  void toStack(std::size_t &k);
  void toStack(Element oper);
  void toStack(name_pair np, std::size_t &k);
  void operatorRoat(Element oper);
  void impasToPost();
  void closeOper();

 public:
  double countX(std::string &x, std::string place);
  ModelCalc();
  double result();
  void setX(std::string &x);
  void setExpression(std::string &input);
};

class Model : public ModelCalc {
 private:
  friend class Controller;
  point_vec points;
  double xmax, xmin, ymax, ymin, grids;
  double width, height, ynormal;
  bool pointC, gridsAuto;
  grid_vec xGrids;
  grid_vec yGrids;
  void countGridLists();
  void countPointMas();
  void moveX(double x);
  void moveY(double y);
  double yVTPoint(double y);
  int xVTPoint(double x);
  void pushPoint(double x, double y);
  void reCount();
  void resize(int h, int w);
  void gridsRecount();
  void findGraph();
  void createMaxMin(double val);
  bool oneSearch();
  bool onePMSearch();
  void twoAuto(double &a, double &b);
  void xMinMax();
  void yMinMax();

 public:
  void clear();
  Model() : ModelCalc() {}
  void graph();
  void setXY(std::string &xMax, std::string &xMin, std::string &yMax,
             std::string &yMin);
  void setHW(int h, int w);
  void setPointCenter(bool pointCenter) { pointC = pointCenter; }
  void gridCount(std::string gridStep);
  void setScale(bool scal);
  void setMove(double x, double y);
  void setMoveX(double x);
  void setMoveY(double y);
  void onPointCenter();
};

}  // namespace s21

#endif
