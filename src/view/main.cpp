#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  Widget w;
  w.setController(&controller);
  w.show();
  return a.exec();
}
