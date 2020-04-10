#include "Ship.h"

//Constructors / Destructors
Ship::Ship(float x, float y, sf::Texture& texture)
{
    InitVariables();
    InitComponents();

    SetTexture(texture);
    SetPosition(x, y);
    SetTextureRect(40, 40, 40, 45);
    SetRotation(0.f);
    SetOrigin(sf::Vector2f(20.f, 20.f));
}

Ship::~Ship()
{
}

//Initializer functions
void Ship::InitVariables()
{
}

void Ship::InitComponents()
{
    CreateMovementComponent(200.f, 5.f, 1.f);
}
