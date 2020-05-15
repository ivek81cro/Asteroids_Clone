#include "stdafx.h"
#include "MovementComponent.h"

/**
    Class for movement of entities
 */
//Constructors / Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_velocity, const float& acceleration,
                                     const float& deceleration, const float& angle, const Movement_e& name)
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

/**
    Returns maximal velocity for entity
 */
//Accessors
const float& MovementComponent::GetMaxVelocity() const
{
    return max_velocity_;
}

/**
    Returns current velocity for entity
 */
const sf::Vector2f& MovementComponent::GetVelocity() const
{
    return velocity_;
}

/**
    Move entity, ship has additional calculations
 */
//Functions
void MovementComponent::Move(const float dir_x, const float dir_y, const float& delta)
{
    //Ship rotation
    if (dir_x != 0)
    {
        sprite_.rotate(dir_x * 300.f * delta);
    }
    //Ship movement forward-backward
    if (name_ == Movement_e::Ship)
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
        //Asteroids and bullets movement
        velocity_ = direction_ * max_velocity_;
    }
}

/**
    Limiter for velocity of entity, ship has deceleration
 */
void MovementComponent::CheckMaxVelocity(const float& delta)
{
    //Deceleration -ship only
    if (name_ == Movement_e::Ship)
    {
        velocity_.y *= deceleration_;
        velocity_.x *= deceleration_;
    }
}

/**
    "Continuous screen" for all entities except bullets
 */
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

/**
    Update movement of entities
 */
void MovementComponent::Update(const float& delta, const sf::Vector2u& window_size)
{
    CheckMaxVelocity(delta);
    if (name_ != Movement_e::Bullet)
        CheckPosition(window_size);
    //Final move
    sprite_.move(velocity_ * delta); //Position change
}
