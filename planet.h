#ifndef PLANET_H
#define PLANET_H

class Planet
{

  public:
    Planet(int id, 
      int owner,
      int num_ships,
      int growth_rate,
      float x, float y);

    int id() const;
    int owner() const;
    int numShips() const;
    int growthRate() const;
    float x() const;
    float y() const;

  private:
    int m_id;
    int m_owner;
    int m_num_ships;
    int m_growth_rate;
    float m_x;
    float m_y;

};

#endif

