#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QWheelEvent>

#include "../controller/controller.h"

namespace s21 {

class Widget;

#define GRAPH_PEN QPen(Qt::red)
#define GRID_PEN QPen(Qt::green)
#define ZERO_GRID_PEN QPen(Qt::black)
#define CTRL_POINT_PEN QPen(Qt::blue)
#define TEXT_COLOR Qt::black

class MScene : public QGraphicsScene {
  Q_OBJECT
 private:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
  void keyReleaseEvent(QKeyEvent *keyEvent);
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
  s21::Controller *control;
  int height, width;
  Widget *widget;
  QGraphicsTextItem *pointText;
  QGraphicsEllipseItem *pointEllips;
  bool pointDone = false;

  bool moveMouse = false;
  void controlMove(qreal x);
  void shiftMove(qreal x, qreal y);
  QPen gridPen(double i) { return i == 0 ? ZERO_GRID_PEN : GRID_PEN; }
  void addXText(grid_pair xg);
  void addYText(grid_pair yg);
  void drawGraph();
  void drawGrids();

 public:
  void wheel(bool znak);
  MScene() : QGraphicsScene() {}
  MScene(QGraphicsView *gv, Widget *w) : QGraphicsScene(gv), widget(w) {}
  void setController(Controller *c) { control = c; }
  void draw();
  void setHW(int h, int w);
  void normalMove(qreal x, qreal y);
};

class MGraphicsView : public QGraphicsView {
 public:
  MGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {}
  MGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
      : QGraphicsView(scene, parent) {}

 private:
  bool *graphDone;
  void wheelEvent(QWheelEvent *event);
  void keyPressEvent(QKeyEvent *event);
  MScene *mscene() { return ((MScene *)scene()); }

 public:
  void setGraphD(bool *gd) { graphDone = gd; }
};

}  // namespace s21

#endif
