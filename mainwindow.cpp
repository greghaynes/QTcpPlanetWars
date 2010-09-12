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

  setBotSelected(false);
}

void MainWindow::setBotPath(const QString &path)
{
  botPath = path;
}

void MainWindow::selectPath()
{
  QFileDialog *dialog = new QFileDialog(this, "Locate your bot");
  connect(dialog, SIGNAL(fileSelected(const QString&)),
          this, SLOT(setBotPath(const QString&)));
  dialog->show();
}

void MainWindow::setBotSelected(bool value)
{
  ui->usernameLineEdit->setEnabled(value);
  ui->playGamePushButton->setEnabled(value);
}

#include "mainwindow.moc"

