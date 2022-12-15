#include <QWheelEvent>

#include "widget.h"

void Widget::setCursorPlace() { cursorPlace = (QTextEdit *)sender(); }

void Widget::setCursorPlaceAuto() {
  cursorPlace = (QTextEdit *)sender();
  if (((QTextEdit *)sender())->toPlainText() == "auto" &&
      !(((QTextEdit *)sender())->isReadOnly()))
    ((QTextEdit *)sender())->clear();
}

void Widget::cXYChanged() {
  changeTextVar(ui->ymintext);
  if (!ui->pointcenter->isChecked()) changeTextVar(ui->ymaxtext);
}

void Widget::pCenterChanged() {
  if (ui->pointcenter->isChecked() && graphDone) {
    control->onPointCenter();
    scene->draw();
  }
  if (!(ui->ymintext->isReadOnly())) changeTextVar(ui->ymaxtext);
  if (!(ui->xmintext->isReadOnly())) changeTextVar(ui->xmaxtext);
}

void Widget::offPCenter() {
  if (!(ui->pointcenter->isChecked())) return;
  control->setPointCenter(false);
  ui->pointcenter->setChecked(false);
  onText(ui->xmaxtext);
}

void Widget::offCXY() {
  if (!(ui->connectxy->isChecked())) return;
  onText(ui->ymintext);
  onText(ui->ymaxtext);
}

void Widget::click() {
  cursorPlace->insertPlainText(((QPushButton *)sender())->text());
}

void Widget::clickResult() {
  control->setExpression(getText(ui->inputtext));
  tryCatch([&]() {
    ui->outputtext->setText(
        QString::number(control->count(getText(ui->xtext)), 'g', 6));
  });
}

void Widget::clickClear() { cursorPlace->textCursor().deletePreviousChar(); }

void Widget::setAutoX() {
  if (ui->xmintext->isReadOnly()) onText(ui->xmintext);
  if (!(ui->pointcenter->isChecked())) onText(ui->xmaxtext);
  if (ui->connectxy->isChecked()) {
    offText(ui->ymintext);
    offText(ui->ymaxtext);
  }
  ui->xmintext->setText("auto");
  ui->xmaxtext->setText("auto");
}

void Widget::setAutoY() {
  if (ui->ymintext->isReadOnly()) onText(ui->ymintext);
  if (!(ui->pointcenter->isChecked())) onText(ui->ymaxtext);
  if (ui->connectxy->isChecked()) {
    offText(ui->xmintext);
    offText(ui->xmaxtext);
  }
  ui->ymintext->setText("auto");
  ui->ymaxtext->setText("auto");
}

void Widget::setAutoGS() { ui->gridstaptext->setText("auto"); }

void Widget::clickClearAll() {
  ui->inputtext->clear();
  ui->xtext->clear();
  ui->outputtext->setText("result");
}

void Widget::changeTextVar(QTextEdit *text) {
  if (text->isReadOnly())
    onText(text);
  else
    offText(text);
}

void Widget::onText(QTextEdit *text) {
  text->setReadOnly(false);
  text->setStyleSheet("background-color: white;");
}

void Widget::offText(QTextEdit *text) {
  text->setReadOnly(true);
  text->setStyleSheet("background-color: grey;");
}

void Widget::setController(s21::Controller *c) {
  control = c;
  scene->setController(c);
  c->setHW(ui->graphicsView->height(), ui->graphicsView->width());
  hwToScene();
}

void Widget::clickGraph() {
  control->setExpression(getText(ui->inputtext));
  tryCatch([&]() { firstGraph(); });
}

void Widget::firstGraph() {
  control->setPointCenter(ui->pointcenter->isChecked());
  control->graph(getText(ui->xmaxtext), getText(ui->xmintext),
                 getText(ui->ymaxtext), getText(ui->ymintext));
  control->setGridStep(getText(ui->gridstaptext));
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
