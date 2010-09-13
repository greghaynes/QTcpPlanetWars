#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "planet.h"

#include <QList>
#include <QString>
#include <QGraphicsScene>

class GameScene
  : public QGraphicsScene
{
  Q_OBJECT

  public:
    GameScene(QObject *parent = 0);

  public Q_SLOTS:
    void setGameState(const QString &gameState);

  private:
    void resetScene();

    QList<Planet*> *m_planets;

};

#endif

