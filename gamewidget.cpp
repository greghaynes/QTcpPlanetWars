#include "gamewidget.h"

#include <QBrush>
#include <QColor>

#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
{
  m_game_scene = new GameScene();

  ui = new Ui::GameWidget();
  ui->setupUi(this);

  ui->graphicsView->setScene(m_game_scene);
  ui->graphicsView->setAlignment(Qt::AlignCenter);
}

GameWidget::~GameWidget()
{
  delete ui;
}

GameScene &GameWidget::gameScene()
{
  return *m_game_scene;
}

