#include "MovementComponent.h"

MovementComponent::MovementComponent(float max_velocity)
{
    max_velocity_ = max_velocity;
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
void MovementComponent::Move(const float dir_x, const float dir_y)
{
    velocity_.x = max_velocity_ * dir_x;
    velocity_.y = max_velocity_ * dir_y;
}

void MovementComponent::Update(const float& delta)
{
}
