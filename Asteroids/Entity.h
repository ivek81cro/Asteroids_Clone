#ifndef ENTITY_H_
#define ENTITY_H_

#include"MovementComponent.h"

class Entity
{
  public:
    Entity();
    virtual ~Entity();

    //Component functions
    void CreateSprite(sf::Texture* texture);
    void CreateMovementComponent(const float max_velocity);

    //Functions
    virtual void SetPosition(const float x, const float y);
    virtual void SetTextureRect(const int x, const int y, const int height, const int width);
    virtual void Move(const float& delta, const float x, const float y);

    virtual void Update(const float& delta);
    virtual void Render(sf::RenderTarget* target);

  protected:
    sf::Texture* texture_;
    sf::Sprite*  sprite_;

    MovementComponent* movement_component_;

  private:
    //Initializer functions
    void InitVariables();
};

#endif
