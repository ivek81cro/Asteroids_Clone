#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Constants.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Asteroid : public Entity
{
    static const float speed[ 3 ];
    static bool        init_done;
    static sf::Texture tAsteroid;

  public:
    Asteroid(int level);
    Asteroid(sf::Vector2f position, float angle, int level);
    ~Asteroid();

    int         getLevel();
    void        breakDown();
    void        update(sf::Time& elapsedTime);
    static bool Init(const std::string& ImageFile);

  private:
    int          level;
    sf::Vector2f direction;
};

#endif
