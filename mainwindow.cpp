#include "mainwindow.h"
#include "settings.h"
#include "gamewidget.h"

#include <QFileDialog>
#include <QVariant>

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

  QVariant usernameVariant = Settings::instance()->value("username");
  if(usernameVariant != QVariant())
  {
    ui->usernameLineEdit->setText(usernameVariant.toString());
  }

  setWindowTitle("Planet Wars");
  setBotSelected(false);
}

MainWindow::~MainWindow()
{
  Settings::instance()->setValue("username", QVariant(ui->usernameLineEdit->text()));
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
  connect(g, SIGNAL(ended(bool)),
          this, SLOT(gameEnded(bool)));

  GameWidget *gw = new GameWidget();
  connect(g, SIGNAL(state(const QString&)),
          &(gw->gameScene()), SLOT(setGameState(const QString&)));
  gw->show();

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
      term.append("Invalid path to bot, or could not run bot. Is your bot marked as executable?");
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
  term.append(opponent.score());
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

void MainWindow::gameEnded(bool i_won)
{
  Game *g = static_cast<Game*>(sender());
  term.append("You ");
  if(i_won)
    term.append("<font color=\"green\">won</font> ");
  else
    term.append("<font color=\"red\">lost</font> ");
  term.append("against ");
  term.append(g->opponent().username());
  term.append(".<br />");
  updateTerm();
}

void MainWindow::updateTerm()
{
  ui->gameDebugTextEdit->document()->setHtml(term);
}

#include "mainwindow.moc"

