#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float max_velocity)
        : sprite_(sprite)
        , max_velocity_(max_velocity)
{
}

MovementComponent::~MovementComponent()
{
}

///Accessors
const sf::Vector2f& MovementComponent::GetVelocity() const
{
    return velocity_;
}

//Functions
void MovementComponent::Move(const float dir_x, const float dir_y, const float delta)
{
    velocity_.x = max_velocity_ * dir_x;
    velocity_.y = max_velocity_ * dir_y;

    sprite_.move(velocity_ * delta); //Uses velocity
}

void MovementComponent::Update(const float& delta)
{
}
