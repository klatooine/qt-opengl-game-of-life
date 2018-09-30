#include "boardwindow.h"

BoardWindow::BoardWindow(QScreen *screen) : QWindow(screen)
{
  setSurfaceType(OpenGLSurface);
  create();

    // Create an OpenGL context
  m_context = new QOpenGLContext;
  m_context->create();

    // Setup scene and render it
  initializeGL();
  paintGL();
}

void BoardWindow::initializeGL()
{
  m_context->makeCurrent(this);
  initializeOpenGLFunctions();
}

void BoardWindow::paintGL()
{
  m_context->makeCurrent(this);
  glActiveTexture(GL_TEXTURE1);

  glClearColor(0,0,0,1);

  m_context->swapBuffers(this);
  m_context->doneCurrent();
}
