#include "mainwindow.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MainWindow *m = new MainWindow();
  m->show();
  m->selectPath();
  app.exec();
  delete m;
}

