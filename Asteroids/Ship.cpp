#include "Ship.h"

//Constructors / Destructors
Ship::Ship(float x, float y, sf::Texture* texture)
{
    InitVariables();
    InitComponents();

    CreateSprite(texture);
    SetPosition(x, y);
    SetTextureRect(40, 40, 40, 45);
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
    
}
