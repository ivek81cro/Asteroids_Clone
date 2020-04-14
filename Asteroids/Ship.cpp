#include "Ship.h"

//Constructors / Destructors
Ship::Ship(float x, float y, sf::Texture& texture_sheet)
{
    InitVariables();

    SetPosition(x, y);

    CreateMovementComponent(200.f, 400.f, 0.998f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(name_, 10.f, 1, 0, 2, 0, 40, 45);
}

Ship::~Ship()
{
}

//Initializer functions
void Ship::InitVariables()
{
    name_ = "ship";
    alive_ = true;
}

void Ship::InitComponents()
{
    
}

//Functions
sf::Vector2f Ship::GetPosition() const
{
     return sprite_.getPosition();
}

float Ship::GetAngle() const
{
    return sprite_.getRotation();
}
