#include "game.h"

#include <QDebug>
#include <QByteArray>

Game::Game(const QString &hostname,
      quint16 port,
      const QString &username,
      const QString &password,
      const QString &botPath,
      QObject *parent)
  : QObject(parent)
{
  m_username = username;
  m_password = password;
  m_hostname = hostname;
  m_port = port;
  m_botPath = botPath;
  m_started = false;
  my_player.setUsername(username);

  m_socket = new QTcpSocket(this);
  connect(m_socket, SIGNAL(connected()),
    this, SLOT(connected()));
  connect(m_socket, SIGNAL(disconnected()),
    this, SLOT(disconnected()));
  connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
    this, SLOT(connectionError(QAbstractSocket::SocketError)));
  connect(m_socket, SIGNAL(readyRead()),
    this, SLOT(serverResponded()));

  m_process = new QProcess(this);
  m_process->setProcessChannelMode(QProcess::SeparateChannels);
  m_process->setReadChannel(QProcess::StandardOutput);
  connect(m_process, SIGNAL(readyRead()),
    this, SLOT(botResponded()));
  connect(m_process, SIGNAL(started()),
    this, SLOT(botStarted()));
  connect(m_process, SIGNAL(error(QProcess::ProcessError)),
    this, SLOT(botError(QProcess::ProcessError)));
}

void Game::play()
{
  if(m_username.isEmpty())
  {
    emit(error(NO_USERNAME));
    return;
  }
  QList<QString> args;

  if(m_botPath.endsWith(".class"))
  {
    args.append(m_botPath.left(m_botPath.length() - 6));
    m_botPath = "java";
  }
  qDebug() << "executing: " << m_botPath << " with args " << args;
  m_process->start(m_botPath, args);
}

const Player &Game::me()
{
  return my_player;
}

const Player &Game::opponent()
{
  return opponent_player;
}

void Game::connected()
{
  qDebug() << "Connected to server";
  m_socket->write("USER ");
  m_socket->write(m_username.toAscii());
  if(m_password != "")
  {
    m_socket->write(" PASS ");
    m_socket->write(m_password.toAscii());
  }
  m_socket->write("\n");
}

void Game::disconnected()
{
  deleteLater();
}

void Game::connectionError(QAbstractSocket::SocketError socketError)
{
  if(socketError != QAbstractSocket::RemoteHostClosedError)
    emit(error(CONNECTION_ERROR));
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
    {
      QList<QString> words = line.split(" ");
      if(line.startsWith("INFO You currently have"))
      {
        my_player.setScore(words[4]);
        emit(waiting(my_player));
      }
      else if(line.startsWith("INFO Your opponent is"))
      {
        opponent_player.setUsername(words[4]);
        opponent_player.setScore(words[6]);
        emit(started(opponent_player));
      }
      else if(line.startsWith("INFO You WIN"))
      {
        emit(ended(true));
      }
      else if(line.startsWith("INFO You LOSE"))
      {
        emit(ended(false));
      }
      emit(info(line));
      continue;
    }
    else
    {
      if(line.startsWith("go"))
      {
        emit(state(m_state));
        m_state = "";
      }
      m_state.append(line);
      m_process->write(line.toAscii());
    }
  }
}

#include "game.moc"

