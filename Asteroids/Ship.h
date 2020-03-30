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
    void         update(sf::Time& elapsedTime, const sf::Event& event);
    void         onEvent(const sf::Event& event);
    void         shipExplode(sf::Time& elapsedTime);
    void         kill();
    void         moveShip(sf::Time& elapsedTime, const sf::Event& event);
    sf::Vector2f checkPosition();
    void         shieldsUp(sf::Time& elapsedTime);

  private:
    sf::Vector2f mSpeed;
    sf::Texture  mShipTexture;
    int          mXmove;
    int          mYmove;
};

#endif
