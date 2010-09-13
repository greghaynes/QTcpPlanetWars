#include "gamescene.h"

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QFontMetrics>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

GameScene::GameScene(QObject *parent)
{
  m_planets = new QList<Planet*>();
  m_fleets = new QList<Fleet*>();
}

void GameScene::setGameState(const QString &gameState)
{
  Planet *p;
  foreach(p, *m_planets)
    delete p;
  delete m_planets;
  m_planets = new QList<Planet*>();

  Fleet *f;
  foreach(f, *m_fleets)
    delete f;
  delete m_fleets;
  m_fleets = new QList<Fleet*>();

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
      if(tokens[0] == "F")
      {
        m_fleets->append(new Fleet(tokens[1].toInt(),
                                   tokens[2].toInt(),
                                   tokens[3].toInt(),
                                   tokens[4].toInt(),
                                   tokens[5].toInt(),
                                   tokens[6].toInt()));
                    
      }
    }
  }

  resetScene();
}

void GameScene::resetScene()
{
  clear();

  Planet *p;
  QFontMetrics fm = QFontMetrics(font());
  foreach(p, *m_planets)
  {
    int growthRate = p->growthRate() + 1;
    growthRate *= 8;
    QBrush brush;
    if(p->owner() == 1)
      brush = Qt::cyan;
    else if(p->owner() == 2)
      brush = Qt::red;
    else
      brush = Qt::lightGray;
    QGraphicsItem *pitem = addEllipse(p->x() * 20, p->y() * 20, growthRate, growthRate, QPen(), QBrush(brush));
    QString psize = QString::number(p->numShips());
    QGraphicsItem *sizeItem = new QGraphicsTextItem(psize);;
    sizeItem->setPos((p->x() * 20) - (fm.width(psize) / 2.0f) + (growthRate / 2.0f),
                     (p->y() * 20) - (fm.height() / 2.0f) + (growthRate / 2.0f));
    addItem(sizeItem);
  }
}

#include "gamescene.moc"

