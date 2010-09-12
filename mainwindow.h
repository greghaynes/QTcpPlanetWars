#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui
{
  class MainWindow; 
}

class MainWindow
  : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  public Q_SLOTS:
    void setBotPath(const QString &path);
    void selectPath();
    void play();

  private Q_SLOTS:
    void setBotSelected(bool);

  private:
    QString botPath;
    Ui::MainWindow *ui;

};

#endif

