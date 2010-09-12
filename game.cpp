#include "game.h"

#include <QDebug>
#include <QByteArray>

Game::Game(const QString &hostname,
      quint16 port,
      const QString &username,
      const QString &botPath,
      QObject *parent)
  : QObject(parent)
{
  m_username = username;
  m_hostname = hostname;
  m_port = port;
  m_botPath = botPath;
  m_started = false;

  m_socket = new QTcpSocket(this);
  connect(m_socket, SIGNAL(connected()),
    this, SLOT(connected()));
  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError socketError)),
    this, SLOT(connectionError(QAbstractSocket::SocketError socketError)));
  connect(m_socket, SIGNAL(readyRead()),
    this, SLOT(serverResponded()));

  m_process = new QProcess(this);
  m_process->setProcessChannelMode(QProcess::SeparateChannels);
  m_process->setReadChannel(QProcess::StandardOutput);
  connect(m_process, SIGNAL(readyRead()),
    this, SLOT(botResponded()));
  connect(m_process, SIGNAL(started()),
    this, SLOT(botStarted()));
  connect(m_process, SIGNAL(error(ProcessError error)),
    this, SLOT(botError(QProcess::ProcessError error)));
}

void Game::play()
{
  if(m_username.isEmpty())
  {
    emit(error(NO_USERNAME));
    return;
  }

  m_process->start(m_botPath);
}

void Game::connected()
{
  qDebug() << "Connected to server";
  m_socket->write("USER ");
  m_socket->write(m_username.toAscii());
  m_socket->write("\n");
}

void Game::connectionError(QAbstractSocket::SocketError socketError)
{
}

void Game::botStarted()
{
  qDebug() << "Bot running";
  m_socket->connectToHost(m_hostname, m_port);
}

void Game::botError(QProcess::ProcessError e)
{
  emit(error(BAD_BOT_PATH));
}

void Game::botResponded()
{
  QByteArray data = m_process->readAll();
  qDebug() << data;
  m_socket->write(data);
}

void Game::serverResponded()
{
  while(m_socket->bytesAvailable() > 0)
  {
    QString line = m_socket->readLine();
    if(line.isEmpty())
      return;
    qDebug() << line;
    if(line.startsWith("INFO"))
      continue;
    else
      m_process->write(line.toAscii());
  }
}

#include "game.moc"

