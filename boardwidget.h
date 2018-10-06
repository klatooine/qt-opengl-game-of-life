#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "board.h"

class BoardWidget : public QOpenGLWidget {
  Q_OBJECT

public:
  BoardWidget(QWidget *parent = nullptr);
  void SetBoard(Board * board);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private slots:
  void Draw();
  void CalculateProportion();

private:
  float proportion_ = 1.0f;
  QOpenGLFunctions *f = nullptr;
  Board *board_ = nullptr;

  void SetProportion(int sideSize);
  void DrawCell(int row, int column);
};

#endif // BOARDWIDGET_H
