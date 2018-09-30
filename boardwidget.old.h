#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "board.h"

class BoardWidget : public QOpenGLWidget
{
public:
  BoardWidget(QWidget * parent = nullptr);

  void Draw(Board * board);

private:
  double proportion_ = 1.0;

  void initializeGL();
  void paintGL();

  void SetProportion(int sideSize);
  void DrawAliveCell(int row, int column);
  void DrawDeadCell(int row, int column);
  void DrawCell(int row, int column);

  QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
};

#endif // BOARDWIDGET_H
