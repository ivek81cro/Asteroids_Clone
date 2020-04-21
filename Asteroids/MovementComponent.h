#ifndef MOVEMENTCOMPONENT_H_
#define MOVEMENTCOMPONENT_H_

#include "stdafx.h"

class MovementComponent
{
  public:
    MovementComponent(sf::Sprite& sprite, const float& max_velocity, const float& acceleration,
                      const float& deceleration, const float& angle, const std::string& name);
    virtual ~MovementComponent();

    //Accessors
    const float& GetMaxVelocity() const;
    const sf::Vector2f& GetVelocity() const;

    //Functions
    void Move(const float x, const float y, const float& delta);
    void CheckMaxVelocity(const float& delta);
    void CheckPosition(const sf::Vector2u& window_size);
    void Update(const float& delta, const sf::Vector2u& window_size);

  private:
    sf::Sprite&  sprite_;
    sf::Vector2f direction_;
    std::string  name_;

    float max_velocity_;
    float acceleration_;
    float deceleration_;
    float angle_;

    sf::Vector2f velocity_;

    //Initializer functions
};
#endif
