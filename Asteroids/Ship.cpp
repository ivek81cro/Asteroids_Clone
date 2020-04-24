#include "stdafx.h"
#include "Ship.h"

//Constructors / Destructors
Ship::Ship(float x, float y, sf::Texture& texture_sheet)
{
    InitVariables();

    SetPosition(x, y);

    CreateHitboxComponent(sprite_, 38.f);
    CreateMovementComponent(200.f, 400.f, 0.998f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation("ship", 8.f, 1, 0, 2, 0, 40, 45);
    animation_component_->AddAnimation("ship_l", 5.f, 4, 0, 5, 0, 40, 45);
    animation_component_->AddAnimation("ship_r", 5.f, 7, 0, 8, 0, 40, 45);
    animation_component_->AddAnimation("ship_explode", 5.f, 0, 1, 21, 1, 40, 45);
}

Ship::~Ship()
{
}

//Initializer functions
void Ship::InitVariables()
{
    name_           = "ship";
    animation_name_ = name_;
    level_          = 0;
    invulnerability_ = true;
    shield_timer_    = 5.f;
}

void Ship::InitComponents()
{
}

//Functions
void Ship::ResetAnimationName()
{
    animation_name_ = name_;
}

void Ship::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (exploding_)
    {
        if (animation_component_->Play("ship_explode", delta, true))
        {
            exploding_ = false;
            alive_     = false;
        }
    }
    else
    {
        if (shield_timer_ > 0.f)
            shield_timer_ -= delta;
        else
            invulnerability_ = false;

        Entity::Update(delta, window_size);
    }
}

void Ship::Move(const float dir_x, const float dir_y, const float& delta)
{
    Entity::Move(dir_x, dir_y, delta);

    //Ship animation preset based on movement

    if (dir_x > 0)
        animation_name_ = "ship_r";
    else if (dir_x < 0)
        animation_name_ = "ship_l";
    else
        animation_name_ = name_;
}

void Ship::SetAlive(bool is_alive)
{
    exploding_ = true;
}

bool Ship::ShieldsUp()
{
    return invulnerability_;
}

sf::Vector2f Ship::GetPosition() const
{
    return sprite_.getPosition();
}

float Ship::GetAngle() const
{
    return sprite_.getRotation();
}
