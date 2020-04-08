#ifndef SHIP_H_
#define SHIP_H_
#include "Entity.h"

class Ship : public Entity
{
  public:
    Ship(float x, float y, sf::Texture& texture);
    virtual ~Ship();

    //Functions

  private:
    //Variables

    //Initializer functions
    void InitVariables();
    void InitComponents();
};

#endif
