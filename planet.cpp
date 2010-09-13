#include "planet.h"

Planet::Planet(int id, int owner, int num_ships,
  int growth_rate, float x, float y)
{
  m_id = id;
  m_owner = owner;
  m_num_ships = num_ships;
  m_growth_rate = growth_rate;
  m_x = x;
  m_y = y;
}

int Planet::id() const
{
  return m_id;
}

int Planet::owner() const
{
  return  m_owner;
}

int Planet::numShips() const
{
  return m_num_ships;
}

int Planet::growthRate() const
{
  return m_growth_rate;
}

float Planet::x() const
{
  return m_x;
}

float Planet::y() const
{
  return m_y;
}

