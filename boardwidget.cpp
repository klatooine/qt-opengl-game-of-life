#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget * parent) : QOpenGLWidget (parent) {
}

void BoardWidget::SetBoard(Board * board) {
  board_ = board;

  CalculateProportion();

  connect(board_, SIGNAL(Changed()), this, SLOT(Draw()));
  connect(board_, SIGNAL(SizeChanged()), this, SLOT(CalculateProportion()));
}

void BoardWidget::initializeGL() {
  f = QOpenGLContext::currentContext()->functions();

  makeCurrent();

  f->initializeOpenGLFunctions();
  f->glClearColor(0,0,0,0);
  f->glDisable(GL_TEXTURE_2D);
  f->glDisable(GL_DEPTH_TEST);
  f->glDisable(GL_COLOR_MATERIAL);
  f->glEnable(GL_BLEND);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BoardWidget::resizeGL(int w, int h) {
  makeCurrent();

  f->glViewport(0, 0, w, h);
}

void BoardWidget::paintGL() {
  makeCurrent();

  f->glClear(GL_COLOR_BUFFER_BIT);

  if (board_) {
    int sideSize = board_->GetSideSize();

    for (int rowIndex = 0; rowIndex < sideSize; rowIndex++) {
      for (int columnIndex = 0; columnIndex < sideSize; columnIndex++) {
        if(board_->IsCellAlive(rowIndex, columnIndex)) {
          DrawAliveCell(rowIndex, columnIndex);
        }
        else {
          DrawDeadCell(rowIndex, columnIndex);
        }
      }
    }
  }
}

void BoardWidget::Draw() {
  makeCurrent();

  update();
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
  GLfloat x = -1.0f + static_cast<float>(column * proportion_);
  GLfloat y = 1.0f - static_cast<float>(row * proportion_);

  glVertex3f(x, y, 0);
  glVertex3f( x, y - proportion_, 0);
  glVertex3f( x + proportion_, y - proportion_, 0);
  glVertex3f( x, y, 0);
  glVertex3f( x + proportion_, y, 0);
  glVertex3f( x + proportion_, y - proportion_, 0);
}

void BoardWidget::SetProportion(int sideSize) {
  proportion_ = 2.0f / sideSize;
}

void BoardWidget::CalculateProportion() {
  int sideSize = board_->GetSideSize();

  SetProportion(sideSize);
}
