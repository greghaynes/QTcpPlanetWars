#include "game.h"


Game::Game(QObject *parent)
  : QObject(parent)
{
  m_socket = new QTcpSocket(this);
}

void Game::play(const QString &path,
  const QString &hostname,
  quint16 port)
{
  m_socket->connectToHost(hostname, port);
}

QTcpSocket *Game::socket()
{
  return m_socket;
}

void Game::connected()
{
}

void Game::connectionError(QAbstractSocket::SocketError socketError)
{
}

#include "game.moc"

