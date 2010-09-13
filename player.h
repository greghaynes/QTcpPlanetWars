#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player
  : public QObject
{

  public:
    Player(const QString &username = "",
           int score = 0,
           QObject *parent = 0);

    const QString &username() const;
    int score() const;
    void setScore(int score);
    void setUsername(const QString &username);

  private:
    QString m_username;
    int m_score;

};

#endif

