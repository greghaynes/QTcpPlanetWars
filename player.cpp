#include "player.h"

Player::Player(const QString &username,
               int score,
               QObject *parent)
  : QObject(parent)
{
  m_score = score;
}

const QString &Player::username() const
{
  return m_username;
}

int Player::score() const
{
  return m_score;
}

void Player::setScore(int score)
{
  m_score = score;
}

void Player::setUsername(const QString &username)
{
  m_username = username;
}

