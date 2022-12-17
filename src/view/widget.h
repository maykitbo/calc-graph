#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QWheelEvent>
#include <QWidget>

#include "./ui_widget.h"
#include "graphicsview.h"

namespace s21 {

class Widget : public QWidget {
  Q_OBJECT
 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  void setController(Controller *c);
  void setSceneN();
  void offPCenter();
  void offCXY();
  void doubleClick();
 private slots:
  void click();
  void clickResult();
  void clickClear();
  void clickClearAll();
  void clickGraph();
  void setCursorPlace();
  void setCursorPlaceAuto();
  void setAutoX();
  void setAutoY();
  void setAutoGS();
  void cXYChanged();
  void pCenterChanged();
  void enterPressed();

 private:
  void keyPressEvent(QKeyEvent *event);
  void resizeEvent(QResizeEvent *event);
  Ui::Widget *ui;
  Controller *control;
  MTextEdit *cursorPlace;
  MScene *scene;
  void hwToScene() {
    scene->setHW(ui->graphicsView->height(), ui->graphicsView->width());
  }
  bool graphDone = false;
  void firstGraph();
  template <class T>
  void tryCatch(const T &func) {
    try {
      func();
    } catch (std::runtime_error const &er) {
      ui->outputtext->setText(QString::fromStdString(er.what()));
    }
  }

 public:
  bool graphD() { return graphDone; }
};

}  // namespace s21

#endif  // WIDGET_H
