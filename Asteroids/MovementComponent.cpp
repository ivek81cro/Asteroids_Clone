#include "MovementComponent.h"

//Constructors / Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, float max_velocity, float acceleration, float deceleration)
        : sprite_(sprite)
        , max_velocity_(max_velocity)
        , acceleration_(acceleration)
        , deceleration_(deceleration)
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
void MovementComponent::Move(const float dir_x, const float dir_y, const float& delta)
{
    //Acceeration
    sprite_.rotate(dir_x * 300.f * delta);

    if (dir_y != 0)
    {
        float rotation = sprite_.getRotation() + 90;
        float x_pos    = cos(rotation * 0.017453f);
        float y_pos    = sin(rotation * 0.017453f);

        velocity_.x += acceleration_ * dir_y * delta * x_pos;
        velocity_.y += acceleration_ * dir_y * delta * y_pos;
    }
}

void MovementComponent::CheckMaxVelocity(const float& delta)
{
    if ((velocity_.x * velocity_.x) > (max_velocity_ * max_velocity_))
        velocity_.x = velocity_.x > 0 ? max_velocity_ : -max_velocity_;

    if ((velocity_.y * velocity_.y) > (max_velocity_ * max_velocity_))
        velocity_.y = velocity_.y > 0 ? max_velocity_ : -max_velocity_;    
}

void MovementComponent::CheckPosition(const sf::Vector2u& window_size)
{
    sf::Vector2f position = sprite_.getPosition();

    if (position.x > window_size.x)
        position.x = 0;
    if (position.x < 0)
        position.x = window_size.x;

    if (position.y > window_size.y)
        position.y = 0;
    if (position.y < 0)
        position.y = window_size.y;

    sprite_.setPosition(position);
}

void MovementComponent::Update(const float& delta, const sf::Vector2u& window_size)
{
    CheckMaxVelocity(delta);
    CheckPosition(window_size);
    //Final move
    sprite_.move(velocity_ * delta); //Uses velocity
}
