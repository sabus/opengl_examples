#include <iostream>
#include <QApplication>
#include <glwidget.h>
#include <glengine/logger.h>
#include <log4cpp/PropertyConfigurator.hh>
using namespace std;

int main(int argc, char** argv) {
  std::string initFileName = "logger.properties";
  log4cpp::PropertyConfigurator::configure(initFileName);
  QApplication app(argc, argv);
  QGLFormat glFormat;
 glFormat.setVersion(3, 3);
 glFormat.setProfile(QGLFormat::CoreProfile);
  GLWidget qglWidget(glFormat);
  qglWidget.resize(640, 480);
  qglWidget.show();  // widget must be shown to set window size, otherwise context will not be created properly !!!

  return app.exec();
}

