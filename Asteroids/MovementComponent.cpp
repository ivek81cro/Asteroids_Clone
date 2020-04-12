#include "MovementComponent.h"

//Constructors / Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_velocity, const float& acceleration, const float& deceleration,
                                     const float& angle, const std::string& name)
        : sprite_(sprite)
        , max_velocity_(max_velocity)
        , acceleration_(acceleration)
        , deceleration_(deceleration)
        , name_(name)
        , angle_(angle)
{
    direction_ = {cos(angle * 0.017453f), sin(angle * 0.017453f)};
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
    if (name_ == "ship")
        MoveShip(dir_x, dir_y, delta);

    if (name_ == "asteroid" || name_== "bullet")
        MoveAsteroid();
}

void MovementComponent::MoveShip(const float dir_x, const float dir_y, const float& delta)
{
    //Acceeration
    if (dir_x != 0)
        sprite_.rotate(dir_x * 300.f * delta);

    if (dir_y != 0)
    {
        float angle = sprite_.getRotation() + 90;
        if (acceleration_ != 0)
        {
            direction_ = {cos(angle * 0.017453f), sin(angle * 0.017453f)};

            velocity_.x += acceleration_ * dir_y * delta * direction_.x;
            velocity_.y += acceleration_ * dir_y * delta * direction_.y;
        }
    }
}

void MovementComponent::MoveAsteroid()
{
    velocity_ = direction_ * 100.f;
}

void MovementComponent::CheckMaxVelocity(const float& delta)
{
    if ((velocity_.x * velocity_.x) > (max_velocity_ * max_velocity_))
        velocity_.x = velocity_.x > 0 ? max_velocity_ : -max_velocity_;

    if ((velocity_.y * velocity_.y) > (max_velocity_ * max_velocity_))
        velocity_.y = velocity_.y > 0 ? max_velocity_ : -max_velocity_;

    //Deceleration
    if (deceleration_ != 0)
    {
        velocity_.y *= deceleration_;
        velocity_.x *= deceleration_;
    }
}

void MovementComponent::CheckPosition(const sf::Vector2u& window_size)
{
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
    CheckPosition(window_size);
    //Final move
    sprite_.move(velocity_ * delta); //Uses velocity
}
