#ifndef ENTITY_H_
#define ENTITY_H_

#include"MovementComponent.h"

class Entity
{
  public:
    Entity();
    virtual ~Entity();

    //Component functions
    void SetTexture(sf::Texture& texture);
    void CreateMovementComponent(const float max_velocity, const float acceleration, const float deceleration);

    //Functions
    virtual void SetPosition(const float x, const float y);
    virtual void SetTextureRect(const int x, const int y, const int height, const int width);
    virtual void SetRotation(const float r);
    virtual void SetOrigin(const sf::Vector2f origin);
    virtual void Move(const float x, const float y, const float& delta);

    virtual void Update(const float& delta, const sf::Vector2u& window_size);
    virtual void Render(sf::RenderTarget* target);

  protected:
    sf::Sprite  sprite_;

    MovementComponent* movement_component_;

  private:
    //Initializer functions
    void InitVariables();
};

#endif
