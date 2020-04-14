#ifndef SHIP_H_
#define SHIP_H_
#include "Entity.h"

class Ship : public Entity
{
  public:
    Ship(float x, float y, sf::Texture& texture_sheet);
    virtual ~Ship();

    Ship(const Ship&) = delete;
    void operator=(const Ship&) = delete;

    //Functions
    void Update();

    sf::Vector2f GetPosition() const;
    float        GetAngle() const;

  private:
    //Variables

    //Initializer functions
    void InitVariables();
    void InitComponents();
};

#endif
