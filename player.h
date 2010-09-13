#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player
  : public QObject
{

  public:
    Player(const QString &username = "",
           const QString &score = "",
           QObject *parent = 0);

    const QString &username() const;
    const QString &score() const;
    void setScore(const QString &score);
    void setUsername(const QString &username);

  private:
    QString m_username;
    QString m_score;

};

#endif

