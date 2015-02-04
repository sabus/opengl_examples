#include "glwidget.h"
#include <glengine/renderer.h>
#include <glengine/logger.h>
GLWidget::GLWidget(const QGLFormat& format,QWidget *parent)
    : QGLWidget(format,parent),mRenderer(nullptr) {
}

void GLWidget::initializeGL() {
  if(this->context()->isValid())
    mRenderer = new Renderer();
  else
      ERROR() << "Failed to initialize requested context";
}

/// @note camera decides renderer size
void GLWidget::resizeGL(int width, int height) {
//    if(mRenderer)
//        mRenderer->resize(width,height);
//    else
//        ERROR() << "Cannot resize renderer. It is not initialized";
//    updateGL();
}

void GLWidget::paintGL() {
  if(mRenderer)
    mRenderer->render();
  else
      ERROR() << "Cannot paint renderer. It is not initialized";
}
