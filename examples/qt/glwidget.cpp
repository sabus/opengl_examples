#include "glwidget.h"
#include <renderer.h>
#include <logger.h>
GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent) {
}

void GLWidget::initializeGL() {
  QGLFormat qglFormat;
  qglFormat.setVersion(3, 3);  // get expected output with (3,3) and below, else blank window
  qglFormat.setProfile(QGLFormat::CompatibilityProfile);
  qglFormat.setSampleBuffers(true);
  this->setFormat(qglFormat);
  QString versionString(
      QLatin1String(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
  DEBUG()<< "Driver Version String:" << versionString.toStdString();
  DEBUG()<< "Is valid context: " << this->context()->isValid();
  mRenderer = new Renderer();
  glClearColor(1.0, 0.0, 1.0, 1.0);
  // initialize your engine
}

/// @note camera decides renderer size
void GLWidget::resizeGL(int width, int height) {
  // resize your engine
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);
//    // call engine draw function
}
