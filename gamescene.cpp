#include "gamescene.h"

GameScene::GameScene(QObject *parent)
{
  m_planets = new QList<Planet*>();
}

void GameScene::setGameState(const QString &gameState)
{
  Planet *p;
  foreach(p, *m_planets)
    delete p;
  delete m_planets;
  m_planets = new QList<Planet*>();

  QList<QString> lines = gameState.split("\n");
  QString line;
  int planet_id = 0;
  foreach(line, lines) {
    QList<QString> tokens = line.split(" ");
    if(tokens.size() < 1)
      continue;
    else
    {
      if(tokens[0] == "P")
      {
        m_planets->append(new Planet(planet_id,
                         tokens[3].toInt(),
                         tokens[4].toInt(),
                         tokens[5].toInt(),
                         tokens[1].toFloat(),
                         tokens[2].toFloat()));
        ++planet_id;
      }
    }
  }
}

void GameScene::resetScene()
{
  clear();

  Planet *p;
  foreach(p, *m_planets)
  {
    addEllipse(p->x(), p->y(), p->growthRate(), p->growthRate());
  }
}

