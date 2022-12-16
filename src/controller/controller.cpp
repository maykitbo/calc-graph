
#include "controller.h"

using namespace s21;

double Controller::count(std::string x) {
  model->setX(x);
  return model->result();
}

void Controller::graph(std::string xMax, std::string xMin, std::string yMax,
                       std::string yMin) {
  model->graph();
  model->setXY(xMax, xMin, yMax, yMin);
  model->countPointMas();
}
