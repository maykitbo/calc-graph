#include <QApplication>

#include "widget.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  Widget w;
  w.setController(&controller);
  w.show();
  return a.exec();
}
