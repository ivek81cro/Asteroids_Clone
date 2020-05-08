#include "stdafx.h"
#include "MovementComponent.h"

//Constructors / Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_velocity, const float& acceleration,
                                     const float& deceleration, const float& angle, const std::string& name)
        : sprite_(sprite)
        , max_velocity_(max_velocity)
        , acceleration_(acceleration)
        , deceleration_(deceleration)
        , name_(name)
        , angle_(angle)
{
    //Calculation for bullets and asteroids
    direction_ = {cos(angle * 0.017453f), sin(angle * 0.017453f)};
}

MovementComponent::~MovementComponent()
{
}

//Accessors
const float& MovementComponent::GetMaxVelocity() const
{
    return max_velocity_;
}

const sf::Vector2f& MovementComponent::GetVelocity() const
{
    return velocity_;
}

//Functions
void MovementComponent::Move(const float dir_x, const float dir_y, const float& delta)
{
    //Ship rotation
    if (dir_x != 0)
    {
        sprite_.rotate(dir_x * 300.f * delta);
    }
    //Ship movement forward-backward
    if (name_ == "ship")
    {
        if (dir_y != 0)
        {
            float angle = sprite_.getRotation() + 90.f;

            //Recalculation for ship direction based on rotation
            direction_ = {cos(angle * 0.0174533f), sin(angle * 0.0174533f)};

            //Max speed limit
            float vector_magnitude = sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y);

            if (vector_magnitude < max_velocity_)
            {
                velocity_.x += acceleration_ * dir_y * delta * direction_.x;
                velocity_.y += acceleration_ * dir_y * delta * direction_.y;
            }
        }
    }
    else
    {
        //Asteroids and bullets
        velocity_ = direction_ * max_velocity_;
    }
}

void MovementComponent::CheckMaxVelocity(const float& delta)
{
    //Deceleration -ship only
    if (name_ == "ship")
    {
        velocity_.y *= deceleration_;
        velocity_.x *= deceleration_;
    }
}

void MovementComponent::CheckPosition(const sf::Vector2u& window_size)
{
    //Infinite screen for asteroids and ship
    sf::Vector2f position = sprite_.getPosition();

    if (position.x > window_size.x)
        position.x = 0;
    if (position.x < 0)
        position.x = static_cast<float>(window_size.x);

    if (position.y > window_size.y)
        position.y = 0;
    if (position.y < 0)
        position.y = static_cast<float>(window_size.y);

    sprite_.setPosition(position);
}

void MovementComponent::Update(const float& delta, const sf::Vector2u& window_size)
{
    CheckMaxVelocity(delta);
    if (name_ == "asteroid" || name_ == "ship")
        CheckPosition(window_size);
    //Final move
    sprite_.move(velocity_ * delta); //Position change
}
