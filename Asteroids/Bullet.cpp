#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(const float& x, const float& y, sf::Texture& texture_sheet, const float& angle,
               const float& scale_factor, const EntityName_e name)
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



//Initializer functions
void Bullet::InitVariables()
{
    animation_name_ = Animation_e::Bullet_default;
    lifetime_       = 1.f;
    sprite_.setRotation(angle_ - 90);
    max_velocity_ = 1000.f * scale_factor_;
    movement_name_ = Movement_e::Bullet;
}

/**
    Initialize components needed for entity behaviour
 */
void Bullet::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 32 * 0.25f * scale_factor_);
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(animation_name_, 10.f, 0, 0, 0, 0, 64, 32);
}

/**
    Set scale of a bullet
 */
void Bullet::SetScale(const sf::Vector2f& factor)
{
    sprite_.setScale(factor);
}

/**
    Set lifetime of bullet, since no continuous screen and save
    on number of entities in vector
 */
void Bullet::SetLifeTime(const float& delta)
{
    lifetime_ -= delta;
    if (lifetime_ < 0)
    {
        alive_ = false;
    }
}

void Bullet::Update(const float& delta, const sf::Vector2u& window_size)
{
    SetLifeTime(delta);

    Entity::Update(delta, window_size);
}
