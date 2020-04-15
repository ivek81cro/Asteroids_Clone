#include "Ship.h"

//Constructors / Destructors
Ship::Ship(float x, float y, sf::Texture& texture_sheet)
{
    InitVariables();

    SetPosition(x, y);

    CreateHitboxComponent(sprite_, -20.f, -20.f, 40.f);
    CreateMovementComponent(200.f, 400.f, 0.998f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation("ship", 5.f, 1, 0, 2, 0, 40, 45);
    animation_component_->AddAnimation("ship_l", 2.5f, 4, 0, 5, 0, 40, 45);
    animation_component_->AddAnimation("ship_r", 2.5f, 7, 0, 8, 0, 40, 45);
    animation_component_->AddAnimation("ship_explode", 5.f, 0, 1, 21, 1, 40, 45);

    exploding_ = true;
}

Ship::~Ship()
{
}

//Initializer functions
void Ship::InitVariables()
{
    name_           = "ship";
    animation_name_ = name_;
}

void Ship::InitComponents()
{
}

//Functions
void Ship::ResetAnimationName()
{
    animation_name_ = name_;
}

sf::Vector2f Ship::GetPosition() const
{
    return sprite_.getPosition();
}

float Ship::GetAngle() const
{
    return sprite_.getRotation();
}
