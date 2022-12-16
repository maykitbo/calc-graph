#include "widget.h"

using namespace s21;

void MScene::draw() {
  clear();
  drawGraph();
  drawGrids();
}

void MScene::drawGraph() {
  point_pair pr(false);
  for (auto p : control->getPoints()) {
    if (pr.flag) addLine(p.x, p.y, pr.x, pr.y, GRAPH_PEN);
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

void MScene::addXText(grid_pair xg) {
  auto tx = addText(QString::number(xg.first, 'g', 4));
  tx->setTransform(QTransform().rotate(-73));
  tx->setPos(xg.second, height - 5);
  tx->setDefaultTextColor(TEXT_COLOR);
}

void MScene::addYText(grid_pair yg) {
  auto tx = addText(QString::number(yg.first, 'g', 4));
  tx->setPos(5, yg.second);
  tx->setDefaultTextColor(TEXT_COLOR);
}
