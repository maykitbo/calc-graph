#include "model.h"

using namespace s21;

void Model::setHW(int h, int w) {
  height = h;
  width = w % 2 ? w - 1 : w;
}

void Model::graph() {
  ModelCalc::clear();
  clear();
  parsing();
}

void Model::clear() {
  points.clear();
  xGrids.clear();
  yGrids.clear();
}

void Model::countPointMas() {
  xn = xmin;
  double step = (xmax - xmin) / (double)(width * 1);
  for (double k = 0; k < width; k += 1) {
    if (fabs(xn) < step / 5) {
      xn = 0;
      pushPoint(k, count());
    }
    pushPoint(k, count());
    xn += step;
  }
}

double Model::yVTPoint(double y) {
  return ((0.5 - (y - ((ymin + ymax) / 2.0)) / (ymax - ymin)) * (double)height);
}

void Model::pushPoint(double x, double y) {
  if (isnan(y) || isinf(y) || y > ymax + fabs(ymax) || y < ymin - fabs(ymin)) {
    if (!points.empty()) points.back().flag = false;
  } else {
    points.emplace_back(true, x, yVTPoint(y), xn, y);
  }
}

void Model::gridCount(std::string gridStep) {
  ModelCalc modX;
  grids = 0;
  if (gridStep == "auto") {
    gridsAuto = true;
    grids = ymax - ymin > xmax - xmin ? (ymax - ymin) / NUM_GRID_AUTO
                                      : (xmax - xmin) / NUM_GRID_AUTO;
  } else {
    gridsAuto = false;
    grids = modX.countX(gridStep, "grid input");
    if (grids <= 0)
      throw std::runtime_error("incorrect grid step");
    else if (grids < (xmax - xmin) / NUM_GRID_MAX) {
      grids = (xmax - xmin) / NUM_GRID_MAX;
    }
  }
  countGridLists();
}

void Model::onPointCenter() {
  clear();
  pointC = true;
  xmax = (xmax - xmin) / 2;
  xmin = -xmax;
  ymax = (ymax - ymin) / 2;
  ymin = -ymax;
  reCount();
}

void Model::reCount() {
  countGridLists();
  countPointMas();
}

int Model::xVTPoint(double x) {
  return (int)((x - xmin) * width / (xmax - xmin));
}

void Model::gridsRecount() {
  bool f = true;
  if (grids <= 1.1 * (xmax - xmin) / NUM_GRID_MAX) {
    grids = (xmax - xmin) / NUM_GRID_MAX;
    f = false;
  }
  if (grids <= 1.1 * (ymax - ymin) / NUM_GRID_MAX) {
    grids = (ymax - ymin) / NUM_GRID_MAX;
    f = false;
  }
  if (f && gridsAuto) {
    grids = xmax - xmin > ymax - ymin ? (ymax - ymin) / NUM_GRID_AUTO
                                      : (xmax - xmin) / NUM_GRID_AUTO;
  }
}

void Model::countGridLists() {
  xGrids.clear();
  yGrids.clear();
  if (xmin < 0 && xmax > 0) {
    for (double k = 0; k > xmin; k -= grids)
      xGrids.emplace_back(k, xVTPoint(k));
    for (double k = 0 + grids; k < xmax; k += grids)
      xGrids.emplace_back(k, xVTPoint(k));
  } else {
    for (double k = xmin + grids; k < xmax; k += grids)
      if (k) xGrids.emplace_back(k, xVTPoint(k));
  }
  double yg = grids * (gridsAuto ? (ymax - ymin) / (xmax - xmin) : 1);
  if (ymin < 0 && ymax > 0) {
    for (double k = 0; k > ymin; k -= yg) yGrids.emplace_back(k, yVTPoint(k));
    for (double k = 0 + yg; k < ymax; k += yg)
      yGrids.emplace_back(k, yVTPoint(k));
  } else {
    for (double k = ymin + yg; k < ymax; k += yg)
      yGrids.emplace_back(k, yVTPoint(k));
  }
}
