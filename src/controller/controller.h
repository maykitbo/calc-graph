#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class Controller {
 private:
  Model *model;

 public:
  Controller(Model *m) : model(m) {}
  double count(std::string x);
  void setExpression(std::string input) { model->setExpression(input); }
  void setHW(int h, int w) { model->setHW(h, w); }

  void graph(std::string xMax, std::string xMin, std::string yMax,
             std::string yMin);
  void setGridStep(std::string gridStep) { model->gridCount(gridStep); }
  point_vec getPoints() const { return model->points; }
  grid_vec getXGrids() const { return model->xGrids; }
  grid_vec getYGrids() const { return model->yGrids; }
  void clear() { model->clear(); }

  double getYMin() { return model->ymin; }
  double getYMax() { return model->ymax; }

  void sendScale(bool scale) { model->setScale(scale); }
  void sendMove(double x, double y) {
    model->clear();
    model->setMove(x, y);
  }
  void sendMoveX(double x) { model->setMoveX(x); }
  void sendMoveY(double y) { model->setMoveY(y); }
  void setPointCenter(bool pc) { model->setPointCenter(pc); }
  void onPointCenter() { model->onPointCenter(); }
  void resize(int h, int w) { model->resize(h, w); }
};

}  // namespace s21

#endif
