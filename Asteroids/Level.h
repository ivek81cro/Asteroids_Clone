#ifndef _LEVEL_H_
#define _LEVEL_H

#include "Asteroid.h"
#include "Bullet.h"
#include "Collider.h"
#include "Ship.h"
#include <SFML/Graphics.hpp>

class Level
{
  public:
    Level();
    ~Level();

    void onEvent(const sf::Event& event);
    void update(float elapsedTime, const sf::Event& event);
    void show(sf::RenderTarget& target);
    void start();

  private:
    Ship                  ship;
    std::vector<Bullet>   bullets;
    std::vector<Asteroid> asteroids;
};

#endif
