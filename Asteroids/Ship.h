#ifndef _SHIP_H_
#define _SHIP_H_

#include "Bullet.h"
#include "Constants.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <math.h>

class Ship : public Entity
{
    static const float acceleration;
    static const float max_speed;
    static const float rotation_speed;

  public:
    Ship();
    ~Ship();
    void         reset();
    void         update(float& elapsedTime, const sf::Event& event);
    void         onEvent(const sf::Event& event);
    void         shipExplode(float& elapsedTime);
    void         kill();
    void         moveShip(float& elapsedTime, const sf::Event& event);
    sf::Vector2f checkPosition();
    void         shieldsUp(float& elapsedTime);

  private:
    sf::Vector2f speed;
    sf::Texture  tShip;
    int          x_move;
    int          y_move;
};

#endif
