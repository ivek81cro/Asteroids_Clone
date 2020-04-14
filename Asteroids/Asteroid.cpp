#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, sf::Texture& texture_sheet)
{
    SetPosition(x, y);
    SetRotation(static_cast<float>((rand() % 360)));

    InitVariables();
    InitComponents();
    
    CreateMovementComponent(50.f, 0.f, 0.f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(name_, 5.f, 0, 0, 15, 0, 64, 64);
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
}
