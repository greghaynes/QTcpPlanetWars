#ifndef GAME_H
#define GAME_H

#include "player.h"

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QProcess>

class Game
  : public QObject
{
  Q_OBJECT

  public:
    enum Error {
      NO_USERNAME,
      BAD_BOT_PATH,
      CONNECTION_ERROR,
    };

    Game(const QString &hostname,
      quint16 port,
      const QString &username,
      const QString &password,
      const QString &botPath,
      QObject *parent = 0);

    void play();
    const Player &me();
    const Player &opponent();

  Q_SIGNALS:
    void error(Game::Error e);
    void waiting(const Player &me);
    void started(const Player &opponent);
    void info(const QString&);
    void state(const QString&);
    void ended(bool i_won);

  private Q_SLOTS:
    void connected();
    void disconnected();
    void connectionError(QAbstractSocket::SocketError socketError);
    void botStarted();
    void botError(QProcess::ProcessError error);
    void botResponded();
    void serverResponded();

  private:
    QTcpSocket *m_socket;
    QProcess *m_process;
    QString m_username;
    QString m_password;
    QString m_botPath;
    QString m_hostname;
    quint16 m_port;
    bool m_started;
    Player my_player;
    Player opponent_player;
    QString m_state;

};

#endif

