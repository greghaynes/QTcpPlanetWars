#include "gameview.h"

GameScene::GameScene(QObject *parent = 0)
{
}

void GameScene::setGameState(const QString &gameState)
{
  QList<QString> lines = gameState.split("\n");
  QString line;
  foreach(line, lines) {
    QList<QString> tokens = line.split(" ");
    if(tokens.size() < 1)
      continue;
    else
    {
      if(tokens[0] == "P")
      {
        
      }
    }
  }
}

