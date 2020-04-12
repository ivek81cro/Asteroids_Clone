#ifndef BULLET_H_
#define BULLET_H_

#include "Entity.h"

class Bullet : public Entity
{
  public:
    Bullet(float x, float y, sf::Texture& texture, float angle);
    virtual ~Bullet();

    //Functions
    void SetScale(const sf::Vector2f& factor);
    void SetLifeTime(const float& delta);
  private:
    //Variables
    float lifetime_;

    //Initializer functions
    void InitVariables();
    void InitComponents();
};

#endif
