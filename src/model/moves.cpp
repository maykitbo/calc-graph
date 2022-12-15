#include "model.h"

using namespace s21;

void Model::setScale(bool scal) {
  clear();
  double scalex = (scal ? 1.0 : -1.0) * (xmax - xmin) / SCALE_COEF;
  double scaley = (scal ? 1.0 : -1.0) * (ymax - ymin) / SCALE_COEF;
  xmax += scalex;
  xmin -= scalex;
  ymax += scaley;
  ymin -= scaley;
  gridsRecount();
  reCount();
}

void Model::resize(int h, int w) {
  clear();
  double ry = (double)h * width / ((double)w * height);
  ymin *= ry;
  ymax *= ry;
  width = w;
  height = h;
  // gridsRecount();
  reCount();
}

void Model::setMove(double x, double y) {
  clear();
  moveX(x);
  moveY(y);
  reCount();
}

// ctrl_point Model::controlMove(int x) {
//   // xn = xmin + (x != 0 ? (xmax - xmin) * (double)x / (double)width : 0);
//   // ctrl_point result;
//   // result.xval = xn;
//   // result.yval = count();
//   // result.yp = points[x].y;
//   // std::cout << result.xval << " " << result.yp << " " << result.yval << " " << x << " " << xn << "\n";
//   // return result;
// }

void Model::setMoveX(double x) {
  clear();
  moveX(x);
  reCount();
}

void Model::setMoveY(double y) {
  clear();
  moveY(y);
  reCount();
}

void Model::moveX(double x) {
  if (x == 0 || x > 0 ? xmax > 1e295 : xmin < -1e295) return;
  double dx = x * (xmax - xmin) / MOVE_COEF;
  xmax += dx;
  xmin += dx;
}

void Model::moveY(double y) {
  if (y == 0 || y > 0 ? ymax > 1e295 : ymin < -1e295) return;
  double dy = y * (ymax - ymin) / MOVE_COEF;
  ymax += dy;
  ymin += dy;
}
