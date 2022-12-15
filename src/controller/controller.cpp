
#include "controller.h"

using namespace s21;

double Controller::count(std::string x) {
  // std::cout << *model->expression << "\n";
  model->setX(x);
  // std::cout << *model->expression << "\n";
  return model->result();
}

void Controller::graph(std::string xMax, std::string xMin, std::string yMax,
                       std::string yMin) {
  // model->setPointCenter(pc);
  model->graph();
  model->setXY(xMax, xMin, yMax, yMin);
  model->countPointMas();
}
