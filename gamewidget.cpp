#include "gamewidget.h"
#include "game.h"

#include <QBrush>
#include <QColor>

#include "ui_gamewidget.h"

GameWidget::GameWidget(const QString &title, QWidget *parent)
{
  m_game_scene = new GameScene();

  ui = new Ui::GameWidget();
  ui->setupUi(this);

  ui->graphicsView->setScene(m_game_scene);
  ui->graphicsView->setAlignment(Qt::AlignCenter);
  ui->matchupLabel->setText(title);
}

GameWidget::~GameWidget()
{
  delete ui;
}

GameScene &GameWidget::gameScene()
{
  return *m_game_scene;
}

void GameWidget::setTitle(const QString &title)
{
  ui->matchupLabel->setText(title);
}

void GameWidget::gameStarted(const Player &opponent)
{
  Game *g = static_cast<Game*>(sender());
  QString title = g->me().username();
  title.append(" vs ");
  title.append(g->opponent().username());
  setTitle(title);
}

#include "gamewidget.moc"

