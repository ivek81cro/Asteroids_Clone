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
    void         Reset();
    void         Update(sf::Time& elapsedTime, const sf::Event& event);
    void         OnEvent(const sf::Event& event);
    void         ShipExplode(sf::Time& elapsedTime);
    void         Kill();
    void         MoveShip(sf::Time& elapsedTime, const sf::Event& event);
    sf::Vector2f CheckPosition();
    void         ShieldsUp(sf::Time& elapsedTime);

  private:
    sf::Vector2f mSpeed;
    sf::Texture  mShipTexture;
    int          mXmove;
    int          mYmove;
};

#endif
