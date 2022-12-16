#include "textedit.h"
#include "widget.h"

using namespace s21;

void MTextEdit::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return) {
    emit(enterP());
  } else {
    QTextEdit::keyPressEvent(event);
  }
}

void Widget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return) {
    enterPressed();
  }
  if (event->key() == Qt::Key_Tab) {
    std::cout << "456\n";
  }
}

void MScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  widget->doubleClick();
  QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void Widget::resizeEvent(QResizeEvent *event) {
  if (ui->graphicsView->height() == 0 || ui->graphicsView->width() == 0) return;
  hwToScene();
  if (!graphDone) {
    control->setHW(ui->graphicsView->height(), ui->graphicsView->width());
  } else {
    control->resize(ui->graphicsView->height(), ui->graphicsView->width());
    scene->draw();
    setSceneN();
  }
  QWidget::resizeEvent(event);
}

void MGraphicsView::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() & Qt::ControlModifier) return;
  if (*graphDone) mscene()->wheel(event->angleDelta().ry() < 0);
}

void MGraphicsView::keyPressEvent(QKeyEvent *event) {
  if (!(*graphDone)) return;
  switch (event->key()) {
    case Qt::Key_Left:
      mscene()->normalMove(1, 0);
      break;
    case Qt::Key_Right:
      mscene()->normalMove(-1, 0);
      break;
    case Qt::Key_Up:
      mscene()->normalMove(0, -1);
      break;
    case Qt::Key_Down:
      mscene()->normalMove(0, 1);
      break;
    default:
      QGraphicsView::keyPressEvent(event);
  }
}

void MScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (mouseEvent->button() == Qt::LeftButton) moveMouse = true;
  if (mouseEvent->modifiers() & Qt::ControlModifier) {
    controlMove(mouseEvent->scenePos().x());
  }
}

void MScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (mouseEvent->button() == Qt::LeftButton) moveMouse = false;
  if (pointDone) {
    removeItem(pointEllips);
    removeItem(pointText);
    pointDone = false;
  }
}

void MScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (!moveMouse) return;
  qreal x = mouseEvent->screenPos().rx() - mouseEvent->lastScreenPos().rx();
  qreal y = mouseEvent->lastScreenPos().ry() - mouseEvent->screenPos().ry();
  if (mouseEvent->modifiers() & Qt::ControlModifier) {
    controlMove(mouseEvent->scenePos().x());
  } else if (mouseEvent->modifiers() & Qt::ShiftModifier) {
    shiftMove(x, y);
  } else {
    normalMove(x, y);
  }
}

void MScene::keyReleaseEvent(QKeyEvent *keyEvent) {
  if (keyEvent->key() == Qt::Key_Control && pointDone) {
    removeItem(pointEllips);
    removeItem(pointText);
    pointDone = false;
  }
}

void Widget::enterPressed() {
  control->setExpression(getText(ui->inputtext));
  tryCatch([&]() {
    firstGraph();
    ui->outputtext->setText(
        QString::number(control->count(getText(ui->xtext)), 'g', 6));
  });
}

void MScene::wheel(bool znak) {
  control->sendScale(znak);
  draw();
  widget->setSceneN();
}

void MScene::controlMove(qreal x) {
  for (auto p : control->getPoints()) {
    if (p.x == x) {
      const QString add = "(" + QString::number(p.xval, 'g', 4) + " : " +
                          QString::number(p.yval, 'g', 4) + ")";
      if (!pointDone) {
        pointEllips = addEllipse(x - 3, p.y - 3, 6, 6, CTRL_POINT_PEN);
        pointText = addText(add);
        pointText->setDefaultTextColor(TEXT_COLOR);
      } else {
        pointEllips->setRect(x - 3, p.y - 3, 6, 6);
        pointText->setPlainText(add);
      }
      pointText->setPos(
          x > width / 2 ? x - pointText->boundingRect().width() - 7 : x + 7,
          p.y - 9);
      widget->setSceneN();
      pointDone = true;
      return;
    }
  }
  pointDone = false;
}

void MScene::shiftMove(qreal x, qreal y) {
  widget->offPCenter();
  if (abs(x) > abs(y))
    control->sendMoveX(-x);
  else if (abs(x) < abs(y))
    control->sendMoveY(-y);
  draw();
  widget->setSceneN();
}

void MScene::normalMove(qreal x, qreal y) {
  widget->offPCenter();
  control->sendMove(-x, -y);
  draw();
  widget->setSceneN();
}
