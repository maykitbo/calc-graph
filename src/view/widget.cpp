#include "widget.h"

using namespace s21;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  cursorPlace = ui->inputtext;
  ui->connectxy->setChecked(true);
  ui->pointcenter->setChecked(true);
  offText(ui->xmaxtext);
  offText(ui->ymaxtext);
  offText(ui->ymintext);
  scene = new MScene(ui->graphicsView, this);
  ui->graphicsView->setGraphD(&graphDone);
  for (int k = 0; k < 7; k++) {
    for (int g = 0; g < 4; g++) {
      connect(dynamic_cast<QPushButton *>(
                  ui->layoutbuttons1->itemAtPosition(k, g)->widget()),
              SIGNAL(clicked(bool)), this, SLOT(click()));
    }
  }
  connect(ui->resultbutton, SIGNAL(clicked(bool)), this, SLOT(clickResult()));
  connect(ui->clearbutton, SIGNAL(clicked(bool)), this, SLOT(clickClear()));
  connect(ui->clearallbutton, SIGNAL(clicked(bool)), this,
          SLOT(clickClearAll()));
  connect(ui->graphbutton, SIGNAL(clicked(bool)), this, SLOT(clickGraph()));
  connect(ui->inputtext, SIGNAL(selectionChanged()), this,
          SLOT(setCursorPlace()));
  connect(ui->xtext, SIGNAL(selectionChanged()), this, SLOT(setCursorPlace()));
  connect(ui->xmaxtext, SIGNAL(selectionChanged()), this,
          SLOT(setCursorPlaceAuto()));
  connect(ui->xmintext, SIGNAL(selectionChanged()), this,
          SLOT(setCursorPlaceAuto()));
  connect(ui->ymaxtext, SIGNAL(selectionChanged()), this,
          SLOT(setCursorPlaceAuto()));
  connect(ui->ymintext, SIGNAL(selectionChanged()), this,
          SLOT(setCursorPlaceAuto()));
  connect(ui->gridstaptext, SIGNAL(selectionChanged()), this,
          SLOT(setCursorPlaceAuto()));
  connect(ui->xminmaxbutton, SIGNAL(clicked(bool)), this, SLOT(setAutoX()));
  connect(ui->yminmaxbutton, SIGNAL(clicked(bool)), this, SLOT(setAutoY()));
  connect(ui->gridbutton, SIGNAL(clicked(bool)), this, SLOT(setAutoGS()));
  connect(ui->connectxy, SIGNAL(stateChanged(int)), this, SLOT(cXYChanged()));
  connect(ui->pointcenter, SIGNAL(stateChanged(int)), this,
          SLOT(pCenterChanged()));
    connect(ui->inputtext, SIGNAL(enterP()), this, SLOT(enterPressed()));
    connect(ui->xtext, SIGNAL(enterP()), this, SLOT(enterPressed()));
    connect(ui->xmaxtext, SIGNAL(enterP()), this, SLOT(enterPressed()));
    connect(ui->xmintext, SIGNAL(enterP()), this, SLOT(enterPressed()));
    connect(ui->ymaxtext, SIGNAL(enterP()), this, SLOT(enterPressed()));
    connect(ui->gridstaptext, SIGNAL(enterP()), this, SLOT(enterPressed()));
    connect(ui->ymintext, SIGNAL(enterP()), this, SLOT(enterPressed()));
}

Widget::~Widget() { 
    delete ui;
    delete scene;
}
