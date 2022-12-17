#include "model.h"

using namespace s21;

void Model::setXY(std::string &xMax, std::string &xMin, std::string &yMax,
                  std::string &yMin) {
  ModelCalc modX;
  if (xMax == "auto" && xMin == "auto" && yMax == "auto" && yMin == "auto") {
    findGraph();
  } else if (xMax == "auto" && yMin == "auto" && yMax == "auto") {
    xmin = modX.countX(xMin, "xMin input");
    xMinMax();
    ymax = xmax;
    ymin = xmin;
  } else if (xMax == "auto" && xMin == "auto" && yMax == "auto") {
    ymin = modX.countX(yMin, "yMin input");
    yMinMax();
    xmax = ymax;
    xmin = ymin;
  } else if (xMax == "auto" && yMax == "auto") {
    xmin = modX.countX(xMin, "xMin input");
    xMinMax();
    ymin = modX.countX(yMin, "yMin input");
    yMinMax();
  } else if (yMin == "auto" && yMax == "auto") {
    xmin = modX.countX(xMin, "xMin input");
    xmax = modX.countX(xMax, "xMax input");
    if (xmin >= xmax) throw std::runtime_error("xMin >= xMax");
    twoAuto(ymax, ymin);
  } else {
    ymin = modX.countX(yMin, "yMin input");
    ymax = modX.countX(yMax, "yMax input");
    if (ymin >= ymax) throw std::runtime_error("yMin >= yMax");
    xmax = modX.countX(xMax, "xMax input");
    xmin = modX.countX(xMin, "xMin input");
    if (xmin >= xmax) throw std::runtime_error("xMin >= xMax");
  }
  if (isinf(xmin) || isnan(xmin)) throw std::runtime_error("xmin inf or nan");
  if (isinf(ymin) || isnan(ymin)) throw std::runtime_error("ymin inf or nan");
  if (isinf(xmax) || isnan(xmax)) throw std::runtime_error("xmax inf or nan");
  if (isinf(ymax) || isnan(ymax)) throw std::runtime_error("ymax inf or nan");
  double dy = ((ymax - ymin) * ((height / width) - 1.0)) / 2.0;
  ymax += dy;
  ymin -= dy;
}

void Model::xMinMax() {
  if (xmin == 0) throw std::runtime_error("xMin = xMax = 0");
  if (xmin > 0) xmin *= -1;
  xmax = -xmin;
}

void Model::yMinMax() {
  if (ymin == 0) throw std::runtime_error("yMin = yMax = 0");
  if (ymin > 0) ymin *= -1;
  ymax = -ymin;
}

void Model::twoAuto(double &a, double &b) {
  double max = INFINITY, min = -INFINITY, add = 0;
  for (xn = xmin; xn <= xmax; xn += (xmax - xmin) / 11) {
    add = count();
    if (isnan(add)) continue;
    if (add > min) min = add;
    if (add < max) max = add;
    xn += 0.02 * (xmax - xmin);
  }
  if (isinf(min)) {
    b = xmin;
    a = xmax;
  } else {
    add = (max + min) / 2;
    a = add + (xmax - xmin) / 2;
    b = add - (xmax - xmin) / 2;
  }
}

void Model::findGraph() {
  xn = 0;
  auto y = count();
  if (!isnan(y) && !isinf(y))
    ynormal = y;
  else
    ynormal = INFINITY;
  for (xn = M_PI; xn < 1e300; xn += xn / 10) {
    if (onePMSearch()) return;
    xn += 1.5;
    if (onePMSearch()) return;
    xn += M_E;
    if (onePMSearch()) return;
  }
  if (ynormal == INFINITY) ynormal = 0;
  for (xn = M_PI; xn > 1e-300; xn -= xn / 10) {
    if (onePMSearch()) return;
  }
  createMaxMin(ynormal * 1.2);
}

bool Model::onePMSearch() {
  if (oneSearch()) return true;
  xn *= -1;
  if (oneSearch()) return true;
  xn *= -1;
  return false;
}

bool Model::oneSearch() {
  double y = fabs(count());
  if (!isnan(y) && fabs(y - M_PI) < fabs(ynormal - M_PI)) ynormal = y;
  if (y < fabs(xn)) {
    y = xn;
    if (fabs(y) < 2 * M_PI && fabs(y) > 0.9 * M_PI)
      y = 2 * M_PI;
    else
      y *= 1.2;
    createMaxMin(y);
    return true;
  }
  return false;
}

void Model::createMaxMin(double val) {
  if (fabs(ynormal) < fabs(val)) val = ynormal;
  if ((val > 4 * M_PI || val < -4 * M_PI) && !pointC) {
    if (val < 0) {
      xmin = val;
      xmax = 0.55 * val;
    } else {
      xmax = val;
      xmin = 0.55 * val;
    }
    twoAuto(ymax, ymin);
  } else {
    xmax = (val > 0 ? val : -val);
    ymax = xmax;
    xmin = -xmax;
    ymin = -xmax;
  }
}
