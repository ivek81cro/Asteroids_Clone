#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Texture& texture_sheet, float angle, float scale_factor, std::string name)
        : angle_(angle)
{
    name_         = name;
    scale_factor_ = scale_factor;

    SetPosition(x, y);
    SetScale(sf::Vector2f(0.25f * scale_factor_, 0.25f * scale_factor_));

    InitVariables();
    InitComponents(texture_sheet);
}

Bullet::~Bullet()
{
}

void Bullet::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 32 * 0.25f * scale_factor_);
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(name_, 10.f, 0, 0, 0, 0, 64, 32);
}

void Bullet::SetScale(const sf::Vector2f& factor)
{
    sprite_.setScale(factor);
}

void Bullet::SetLifeTime(const float& delta)
{
    lifetime_ -= delta;
    if (lifetime_ < 0)
    {
        alive_ = false;
    }
}

//Initializer functions
void Bullet::InitVariables()
{
    animation_name_ = name_;
    lifetime_ = 1.f;
    sprite_.setRotation(angle_ - 90);
    max_velocity_ = 1000.f * scale_factor_;
}
