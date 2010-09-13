#include "fleet.h"

Fleet::Fleet(int owner,
             int num_ships,
             int source,
             int destination,
             int trip_length,
             int turns_remaining)
{
  m_owner = owner;
  m_num_ships = num_ships;
  m_source = source;
  m_destination = destination;
  m_trip_length = trip_length;
  m_turns_remaining = turns_remaining;
}

int Fleet::owner() const
{
  return m_owner;
}

int Fleet::numShips() const
{
  return m_num_ships;
}

int Fleet::source() const
{
  return m_source;
}

int Fleet::destination() const
{
  return m_destination;
}

int Fleet::tripLength() const
{
  return m_trip_length;
}

int Fleet::turnsRemaining() const
{
  return m_turns_remaining;
}

