#include "widget.h"

void MScene::draw() {
  clear();
  drawGraph();
  drawGrids();
}

void MScene::drawGraph() {
  s21::point_pair pr(false);
  for (auto p : control->getPoints()) {
    if (pr.flag) addLine(p.x, p.y, pr.x, pr.y, GRAPH_COLOR);
    pr = p;
  }
}

void MScene::drawGrids() {
  for (auto i : control->getXGrids()) {
    addLine(i.second, 0, i.second, height, gridPen(i.first));
    addXText(i);
  }
  for (auto i : control->getYGrids()) {
    addLine(0, i.second, width, i.second, gridPen(i.first));
    addYText(i);
  }
}

void MScene::addXText(s21::grid_pair xg) {
  auto tx = addText(QString::number(xg.first, 'g', 4));
  tx->setTransform(QTransform().rotate(-73));
  tx->setPos(xg.second, height - 5);
}

void MScene::addYText(s21::grid_pair yg) {
  addText(QString::number(yg.first, 'g', 4))->setPos(5, yg.second);
}
