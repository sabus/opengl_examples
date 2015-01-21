#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class Renderer;
class GLWidget : public QGLWidget {
Q_OBJECT
 public:
  explicit GLWidget(QWidget *parent = 0);
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

signals:

 public slots:

 private:
  Renderer* mRenderer;
};

#endif // GLWIDGET_H
