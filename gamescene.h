#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "planet.h"

#include <QList>
#include <QString>
#include <QGraphicsScene>

class GameScene
  : public QGraphicsScene
{

  public:
    GameScene(QObject *parent = 0);

    void setGameState(const QString &gameState);

  private:
    void resetScene();

    QList<Planet*> *m_planets;

};

#endif

