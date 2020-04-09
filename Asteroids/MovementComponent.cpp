#include "MovementComponent.h"

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
void MovementComponent::Move(const float dir_x, const float dir_y, const float delta)
{
    //Acceeration

    velocity_.x += acceleration_ * dir_x;

    if (velocity_.x > 0.f)
    {
        if (velocity_.x > max_velocity_)
            velocity_.x = max_velocity_;
    }
    else if (velocity_.x < 0.f)
    {
        if (velocity_.x < -max_velocity_)
            velocity_.x = -max_velocity_;
    }

    velocity_.y += acceleration_ * dir_y;
    if (velocity_.y > max_velocity_)
        velocity_.y = max_velocity_;
}

void MovementComponent::Update(const float& delta)
{
    //Movement for x
    if (velocity_.x > 0.f)
    {
        //Max velocity check +x
        if (velocity_.x > max_velocity_)
            velocity_.x = max_velocity_;

        //Deceleration +x
        velocity_.x -= deceleration_;
        if (velocity_.x < 0.f)
            velocity_.x = 0;
    }
    else if (velocity_.x < 0.f)
    {
        //Max velocity check -x
        if (velocity_.x < -max_velocity_)
            velocity_.x = -max_velocity_;

        //Deceleration -x
        velocity_.x += deceleration_;
        if (velocity_.x > 0.f)
            velocity_.x = 0;
    }

    //Movement for y
    if (velocity_.y > 0.f)
    {
        //Max velocity check +y
        if (velocity_.y > max_velocity_)
            velocity_.y = max_velocity_;

        //Deceleration +y
        velocity_.y -= deceleration_;
        if (velocity_.y < 0.f)
            velocity_.y = 0;
    }
    else if (velocity_.y < 0.f)
    {
        //Max velocity check -y
        if (velocity_.y < -max_velocity_)
            velocity_.y = -max_velocity_;

        //Deceleration -x
        velocity_.y += deceleration_;
        if (velocity_.y > 0.f)
            velocity_.y = 0;
    }

    //Final move
    sprite_.move(velocity_ * delta); //Uses velocity
}
