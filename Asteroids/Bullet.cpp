#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Texture& texture, float angle)
{
    SetTexture(texture);
    SetPosition(x, y);
    SetTextureRect(14, 0, 30, 50);
    SetRotation(angle - 90);
    SetOrigin(sf::Vector2f(17.f, 27.f));
    SetScale(sf::Vector2f(0.25f, 0.25f));

    InitVariables();
    InitComponents();
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
    lifetime_ = .2f;
    alive_    = true;
}

void Bullet::InitComponents()
{
    CreateMovementComponent(100.f, 0.f, 0.f, sprite_.getRotation());
}
