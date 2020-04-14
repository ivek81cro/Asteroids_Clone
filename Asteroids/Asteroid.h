#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
  public:
    Asteroid(float x, float y, sf::Texture& texture_sheet);
    virtual ~Asteroid();

    Asteroid(const Asteroid&) = delete;
    void operator=(const Asteroid&) = delete;

    //Functions
    void SetScale(const sf::Vector2f& factor);

  private:
    //Variables

    //Initializer functions
    void InitVariables();
    void InitComponents();
};

#endif
