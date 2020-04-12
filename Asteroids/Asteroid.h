#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
  public:
    Asteroid(float x, float y, sf::Texture& texture);
    virtual ~Asteroid();

    //Functions

  private:
    //Variables

    //Initializer functions
    void InitVariables();
    void InitComponents();
};

#endif
