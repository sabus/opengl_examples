#include <iostream>
#include <QtGui>
#include <QApplication>
#include <glwidget.h>
#include <logger.h>
#include <log4cpp/PropertyConfigurator.hh>
using namespace std;

int main(int argc, char** argv) {
  std::string initFileName = "logger.properties";
  log4cpp::PropertyConfigurator::configure(initFileName);

  log4cpp::Category& root = log4cpp::Category::getRoot();
  QApplication app(argc, argv);

  GLWidget qglWidget;
  qglWidget.resize(640, 480);
  qglWidget.show();  // widget must be shown to set window size, otherwise context will not be created properly !!!

  return app.exec();
}

