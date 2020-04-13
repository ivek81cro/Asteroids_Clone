#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, sf::Texture& texture)
{
    SetTexture(texture);
    SetPosition(x, y);
    SetTextureRect(0, 6, 64, 64);
    SetRotation(static_cast<float>((rand() % 360)));
    SetOrigin(sf::Vector2f(32.f, 32.f));

    InitVariables();
    InitComponents();
}

Asteroid::~Asteroid()
{
}

void Asteroid::SetScale(const sf::Vector2f& factor)
{
    sprite_.setScale(factor);
}

//Initializer functions
void Asteroid::InitVariables()
{
    name_ = "asteroid";
    alive_ = true;
}

void Asteroid::InitComponents()
{
    CreateMovementComponent(50.f, 0.f, 0.f, sprite_.getRotation());
}
