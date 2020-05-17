#ifndef BULLET_H_
#define BULLET_H_

#include "Entity.h"

class Bullet : public Entity
{
  public:
    Bullet(float x, float y, sf::Texture& texture, float angle, float scale_factor, EntityName_e name);
    virtual ~Bullet();

    Bullet(const Bullet&) = delete;
    void operator=(const Bullet&) = delete;

    //Functions
    void SetScale(const sf::Vector2f& factor);
    void SetLifeTime(const float& delta);
    void Update(const float& delta, const sf::Vector2u& window_size);

  private:
    //Variables
    float lifetime_;
    float angle_;

    //Initializer functions
    void InitVariables();
    void InitComponents(sf::Texture& texture_sheet);
};

#endif
