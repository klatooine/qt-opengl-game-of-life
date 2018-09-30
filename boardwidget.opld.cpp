#include "boardwidget.old.h"

BoardWidget::BoardWidget(QWidget * parent) : QOpenGLWidget (parent)
{
}

void BoardWidget::initializeGL()
{
  glFuncs->initializeOpenGLFunctions();

  glMatrixMode(GL_MODELVIEW);
}

void BoardWidget::paintGL()
{
}

void BoardWidget::Draw(Board * board) {
  this->context()->makeCurrent(this->context()->surface());

  glPopMatrix();
  glPushMatrix();

  int sideSize = board->GetSideSize();

  SetProportion(sideSize);

  for (int rowIndex = 0; rowIndex < sideSize; rowIndex++) {
    for (int columnIndex = 0; columnIndex < sideSize; columnIndex++) {
      if(board->IsCellAlive(rowIndex, columnIndex)) {
        DrawAliveCell(rowIndex, columnIndex);
      }
      else {
        DrawDeadCell(rowIndex, columnIndex);
      }
    }
  }

  glPopMatrix();

  this->context()->swapBuffers(this->context()->surface());
}

void BoardWidget::DrawDeadCell(int row, int column) {
  glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.0);

    DrawCell(row, column);
  glEnd();
}

void BoardWidget::DrawAliveCell(int row, int column) {
  glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);

    DrawCell(row, column);
  glEnd();
}

void BoardWidget::DrawCell(int row, int column) {
  double x = -1.0 + column * proportion_;
  double y = 1.0 - row * proportion_;

  glVertex3f(x, y, 0);
  glVertex3f( x, y - proportion_, 0);
  glVertex3f( x + proportion_, y - proportion_, 0);
  glVertex3f( x, y, 0);
  glVertex3f( x + proportion_, y, 0);
  glVertex3f( x + proportion_, y - proportion_, 0);
}

void BoardWidget::SetProportion(int sideSize) {
  proportion_ = 2.0 / sideSize;
}
