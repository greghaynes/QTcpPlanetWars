#include "mainwindow.h"

#include <QFileDialog>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  ui = new Ui::MainWindow();
  ui->setupUi(this);

  connect(ui->actionOpen, SIGNAL(triggered(bool)),
    this, SLOT(selectPath()));
  connect(ui->playGamePushButton, SIGNAL(clicked(bool)),
    this, SLOT(play()));

  setBotSelected(false);
}

void MainWindow::setBotPath(const QString &path)
{
  botPath = path;
  setBotSelected(true);
}

void MainWindow::selectPath()
{
  QFileDialog *dialog = new QFileDialog(this, "Locate your bot");
  connect(dialog, SIGNAL(fileSelected(const QString&)),
          this, SLOT(setBotPath(const QString&)));
  dialog->show();
}

void MainWindow::play()
{
  Game *g = new Game("213.3.30.106", 9999,
         ui->usernameLineEdit->text(),
         botPath, this);
  connect(g, SIGNAL(info(const QString&)),
          this, SLOT(gameInfo(const QString&)));
  connect(g, SIGNAL(state(const QString&)),
          this, SLOT(gameState(const QString&)));
  connect(g, SIGNAL(error(Game::Error)),
          this, SLOT(gameError(Game::Error)));
  g->play();
}

void MainWindow::setBotSelected(bool value)
{
  ui->usernameLineEdit->setEnabled(value);
  ui->playGamePushButton->setEnabled(value);
}

void MainWindow::gameError(Game::Error e)
{
  term.append("<font color=\"red\">Error!</font> ");
  switch(e)
  {
    case Game::BAD_BOT_PATH:
      term.append("Invalid path to bot, or could not run bot.");
      break;
    case Game::CONNECTION_ERROR:
      term.append("Could not connect to server.");
      break;
  }
  updateTerm();
}

void MainWindow::gameInfo(const QString info)
{
  QString tinfo = info;
  tinfo.append("<br />");
  term.append(tinfo);
  updateTerm();
}

void MainWindow::gameState(const QString state)
{
}

void MainWindow::updateTerm()
{
  ui->gameDebugTextEdit->document()->setHtml(term);
}

#include "mainwindow.moc"

