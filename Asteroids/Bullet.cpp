#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Texture& texture_sheet, float angle)
{
    SetPosition(x, y);
    SetRotation(angle - 90);
    SetScale(sf::Vector2f(0.25f, 0.25f));

    InitVariables();
    InitComponents();

    CreateMovementComponent(1000.f, 0.f, 0.f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(name_, 10.f, 0, 0, 0, 0, 64, 32);
}

Bullet::~Bullet()
{
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
    name_     = "bullet";
    lifetime_ = 1.f;
    alive_    = true;
}

void Bullet::InitComponents()
{
}
