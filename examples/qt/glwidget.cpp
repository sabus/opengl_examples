#include "glwidget.h"
#include <glengine/renderer.h>
#include <glengine/logger.h>
GLWidget::GLWidget(const QGLFormat& format,QWidget *parent)
    : QGLWidget(format,parent) {
}

void GLWidget::initializeGL() {
  QString versionString(
    QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
  DEBUG()<< "Driver Version String:" << versionString.toStdString();
  DEBUG()<< "Is valid context: " << this->context()->isValid();
  mRenderer = new Renderer();
  glClearColor(1.0, 0.0, 1.0, 1.0);
  updateGL();
  // initialize your engine
}

/// @note camera decides renderer size
void GLWidget::resizeGL(int width, int height) {
  // resize your engine
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);
  mRenderer->render();
//    // call engine draw function
}
