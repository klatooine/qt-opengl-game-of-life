#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include <QWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class BoardWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    BoardWindow(QScreen *screen = nullptr);

protected:
    void initializeGL();
    void paintGL();

    QOpenGLContext *m_context;
};

#endif // BOARDWINDOW_H
