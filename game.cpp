#include "game.h"

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

  m_socket = new QTcpSocket(this);
  connect(m_socket, SIGNAL(connected()),
    this, SLOT(connected()));
  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError socketError)),
    this, SLOT(connectionError(QAbstractSocket::SocketError socketError)));
  connect(m_socket, SIGNAL(readyRead()),
    this, SLOT(serverResponded()));

  m_process = new QProcess(this);
  m_process->setProcessChannelMode(QProcess::SeparateChannels);
  m_process->setReadChannel(QProcess::StandardError);
  connect(m_process, SIGNAL(readyRead()),
    this, SLOT(botResponded()));
  connect(m_process, SIGNAL(started()),
    this, SLOT(botStarted()));
  connect(m_process, SIGNAL(error(QProcess::ProcessError error)),
    this, SLOT(botError(QProcess::ProcessError error)));
}

void Game::play()
{
  
  m_socket->connectToHost(m_hostname, m_port);
}

QTcpSocket *Game::socket()
{
  return m_socket;
}

void Game::connected()
{
  if(m_username.isEmpty())
    emit(error(NO_USERNAME));


}

void Game::connectionError(QAbstractSocket::SocketError socketError)
{
}

void Game::botStarted()
{
}

void Game::botError(QProcess::ProcessError error)
{
}

void Game::botResponded()
{
}

void Game::serverResponded()
{
}

#include "game.moc"

