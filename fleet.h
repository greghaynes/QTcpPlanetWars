#ifndef FLEET_H
#define FLEET_H

class Fleet
{

  public:
    Fleet(int owner,
          int num_ships,
          int source,
          int destination,
          int trip_length,
          int turns_remaining);

    int owner() const;
    int numShips() const;
    int source() const;
    int destination() const;
    int tripLength() const;
    int turnsRemaining() const;

  private:
   int m_owner;
   int m_num_ships;
   int m_source;
   int m_destination;
   int m_trip_length;
   int m_turns_remaining;

};

#endif

