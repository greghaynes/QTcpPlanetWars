#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTcpSocket>

class Game
  : public QObject
{
  Q_OBJECT

  public:
    Game(QObject *parent = 0);

    void play(const QString &path,
      const QString &hostname,
      quint16 port);

    QTcpSocket *socket();

  private Q_SLOTS:
    void connected();
    void connectionError(QAbstractSocket::SocketError socketError);

  private:
    QTcpSocket *m_socket;

};

#endif

