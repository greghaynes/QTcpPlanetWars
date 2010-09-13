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
  connect(g, SIGNAL(error(Game::Error)),
          this, SLOT(gameError(Game::Error)));
  connect(g, SIGNAL(started(const Player&)),
          this, SLOT(gameStarted(const Player&)));
  connect(g, SIGNAL(waiting(const Player&)),
          this, SLOT(gameWaiting(const Player&)));
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
    case Game::NO_USERNAME:
      term.append("No username specified.");
  }
  term.append("<br />");
  updateTerm();
}

void MainWindow::gameStarted(const Player &opponent)
{
  term.append("Game started against <font color=\"blue\">");
  term.append(opponent.username());
  term.append("</font> with ELO score of ");
  term.append(QString(opponent.score()));
  term.append("<br />");
  updateTerm();
}

void MainWindow::gameWaiting(const Player &me)
{
  term.append("Connected as <font color=\"green\">");
  term.append(me.username());
  term.append("</font>.  Waiting for opponent.<br />");
  updateTerm();
}

void MainWindow::updateTerm()
{
  ui->gameDebugTextEdit->document()->setHtml(term);
}

#include "mainwindow.moc"

