#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

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
    void gameError(Game::Error e);
    void gameInfo(const QString info);
    void gameState(const QString state);

  private:
    void updateTerm();

    QString botPath;
    Ui::MainWindow *ui;
    QString term;

};

#endif

