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

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT
 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  void setController(s21::Controller *c);
  void setSceneN();
  void offPCenter();
  void offCXY();
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
  s21::Controller *control;
  QTextEdit *cursorPlace;
  MScene *scene;
  void hwToScene() {
    scene->setHW(ui->graphicsView->height(), ui->graphicsView->width());
  }
  bool graphDone = false;
  void firstGraph();
  void changeTextVar(QTextEdit *text);
  void onText(QTextEdit *text);
  void offText(QTextEdit *text);

  std::string getText(QTextEdit *text) {
    return text->toPlainText().toStdString();
  }

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
#endif  // WIDGET_H
