#include <QWheelEvent>

#include "widget.h"

using namespace s21;

void Widget::setCursorPlace() { cursorPlace = (MTextEdit *)sender(); }

void Widget::setCursorPlaceAuto() {
  cursorPlace = (MTextEdit *)sender();
  if (cursorPlace->toPlainText() == "auto" && !(cursorPlace->isReadOnly())) {
    cursorPlace->clear();
    if (cursorPlace == ui->xmintext && !(ui->xmaxtext->isReadOnly()) &&
        ui->xmaxtext->toPlainText() == "auto")
      ui->xmaxtext->clear();
    else if (cursorPlace == ui->xmaxtext && !(ui->xmintext->isReadOnly()) &&
             ui->xmintext->toPlainText() == "auto")
      ui->xmintext->clear();
    else if (cursorPlace == ui->ymaxtext && !(ui->ymintext->isReadOnly()) &&
             ui->ymintext->toPlainText() == "auto")
      ui->ymintext->clear();
    else if (cursorPlace == ui->ymintext && !(ui->ymaxtext->isReadOnly()) &&
             ui->ymaxtext->toPlainText() == "auto")
      ui->ymaxtext->clear();
  }
}

void Widget::cXYChanged() {
  ui->ymintext->changeTextVar();
  if (!ui->pointcenter->isChecked()) ui->ymaxtext->changeTextVar();
}

void Widget::pCenterChanged() {
  if (ui->pointcenter->isChecked() && graphDone) {
    control->onPointCenter();
    scene->draw();
  }
  if (!(ui->ymintext->isReadOnly())) ui->ymaxtext->changeTextVar();
  if (!(ui->xmintext->isReadOnly())) ui->xmaxtext->changeTextVar();
}

void Widget::doubleClick() {
  if (ui->pointcenter->isChecked()) return;
  ui->pointcenter->setCheckState(Qt::Checked);
}

void Widget::offPCenter() {
  if (!(ui->pointcenter->isChecked())) return;
  control->setPointCenter(false);
  ui->pointcenter->setChecked(false);
  ui->xmaxtext->onText();
}

void Widget::offCXY() {
  if (!(ui->connectxy->isChecked())) return;
  ui->ymintext->onText();
  ui->ymaxtext->onText();
}

void Widget::click() {
  cursorPlace->insertPlainText(((QPushButton *)sender())->text());
}

void Widget::clickResult() {
  control->setExpression(ui->inputtext->getText());
  tryCatch([&]() {
    ui->outputtext->setText(
        QString::number(control->count(ui->xtext->getText()), 'g', 6));
  });
}

void Widget::clickClear() { cursorPlace->textCursor().deletePreviousChar(); }

void Widget::setAutoX() {
  ui->xmintext->setText("auto");
  ui->xmaxtext->setText("auto");
}

void Widget::setAutoY() {
  ui->ymintext->setText("auto");
  ui->ymaxtext->setText("auto");
}

void Widget::setAutoGS() { ui->gridstaptext->setText("auto"); }

void Widget::clickClearAll() {
  ui->inputtext->clear();
  ui->xtext->clear();
  ui->outputtext->setText("result");
}

void MTextEdit::changeTextVar() {
  if (isReadOnly())
    onText();
  else
    offText();
}

void MTextEdit::onText() {
  setReadOnly(false);
  setStyleSheet("background-color: white;");
}

void MTextEdit::offText() {
  setText("auto");
  setReadOnly(true);
  setStyleSheet("background-color: grey;");
}

void Widget::setController(Controller *c) {
  control = c;
  scene->setController(c);
  c->setHW(ui->graphicsView->height(), ui->graphicsView->width());
  hwToScene();
}

void Widget::clickGraph() {
  control->setExpression(ui->inputtext->getText());
  tryCatch([&]() { firstGraph(); });
}

void Widget::firstGraph() {
  control->setPointCenter(ui->pointcenter->isChecked());
  control->graph(ui->xmaxtext->getText(), ui->xmintext->getText(),
                 ui->ymaxtext->getText(), ui->ymintext->getText());
  control->setGridStep(ui->gridstaptext->getText());
  scene->draw();
  setSceneN();
  graphDone = true;
}

void Widget::setSceneN() {
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setRenderHints(QPainter::Antialiasing);
}

void MScene::setHW(int h, int w) {
  height = h;
  width = w;
}
