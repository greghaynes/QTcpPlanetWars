#include "gamescene.h"

#include <QColor>
#include <QPen>
#include <QBrush>

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

  resetScene();
}

void GameScene::resetScene()
{
  clear();

  Planet *p;
  foreach(p, *m_planets)
  {
    int growthRate = p->growthRate();
    if(growthRate < 2) growthRate = 3;
    growthRate *= 6;
    if(p->owner() == 1)
    	addEllipse(p->x() * 18, p->y() * 18, growthRate, growthRate, QPen(), QBrush(Qt::blue));
    else if(p->owner() == 2)
    	addEllipse(p->x() * 18, p->y() * 18, growthRate, growthRate, QPen(), QBrush(Qt::red));
    else
    	addEllipse(p->x() * 18, p->y() * 18, growthRate, growthRate, QPen(), QBrush(Qt::lightGray));
  }
}

#include "gamescene.moc"

