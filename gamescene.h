#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QList>
#include <QString>
#include <QGraphicsScene>

class GameScene
  : public QGraphicsScene
{

  public:
    GameView(QObject *parent = 0);

    void setGameState(const QString &gameState);

  private:
    QList<Planet> m_planets;
    QList<Fleet> m_fleets;

};

#endif

