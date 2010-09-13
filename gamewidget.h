#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "gamescene.h"

#include <QWidget>

namespace Ui
{
  class GameWidget;
}

class GameWidget
  : public QWidget
{

  public:
    GameWidget(QWidget *parent = 0);
    ~GameWidget();

    GameScene &gameScene();


  private:
    Ui::GameWidget *ui;
    GameScene *m_game_scene;

};

#endif

