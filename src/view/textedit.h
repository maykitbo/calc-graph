#ifndef MTEXTEDIT_H
#define MTEXTEDIT_H

#include <QTextEdit>

namespace s21 {

class MTextEdit : public QTextEdit {
  Q_OBJECT
 public:
  MTextEdit() : QTextEdit() {}
  MTextEdit(QWidget *&qw) : QTextEdit(qw) {}
  std::string getText() { return toPlainText().toStdString(); }
  void changeTextVar();
  void onText();
  void offText();

 private:
  void keyPressEvent(QKeyEvent *event);
 signals:
  void enterP();
};

}  // namespace s21

#endif
