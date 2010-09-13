#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "gamescene.h"
#include "player.h"

#include <QWidget>

namespace Ui
{
  class GameWidget;
}

class GameWidget
  : public QWidget
{
  Q_OBJECT

  public:
    GameWidget(const QString &title,
               QWidget *parent = 0);
    ~GameWidget();

    GameScene &gameScene();

  public Q_SLOTS:
    void setTitle(const QString &title);
    void gameStarted(const Player &p);

  private:
    Ui::GameWidget *ui;
    GameScene *m_game_scene;

};

#endif

