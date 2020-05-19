#include "stdafx.h"
#include "Ship.h"

//Constructors / Destructors
Ship::Ship(const float& x, const float& y, sf::Texture& texture_sheet, const float& scale)
        : shield_timer_(3.f)
{
    scale_factor_ = scale;
    sprite_.setScale(scale_factor_, scale_factor_);

    InitVariables();
    InitComponents(texture_sheet);

    SetPosition(x, y);
}

Ship::~Ship()
{
}

//Initializer functions
void Ship::InitVariables()
{
    name_           = EntityName_e::Ship;
    animation_name_ = Animation_e::Ship_shield;
    max_velocity_   = 200.f * scale_factor_;
    acceleration_   = 400.f * scale_factor_;
    movement_name_  = Movement_e::Ship;
    shields_        = true;
}


/**
    Initialize components needed for entity behaviour
 */
void Ship::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 38.f * scale_factor_);
    CreateMovementComponent(max_velocity_, acceleration_, 0.998f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(Animation_e::Ship_default, 8.f, 1, 0, 2, 0, 40, 45);
    animation_component_->AddAnimation(Animation_e::Ship_default_left, 5.f, 4, 0, 5, 0, 40, 45);
    animation_component_->AddAnimation(Animation_e::Ship_default_right, 5.f, 7, 0, 8, 0, 40, 45);
    animation_component_->AddAnimation(Animation_e::Ship_shield, 8.f, 9, 0, 10, 0, 40, 45);
    animation_component_->AddAnimation(Animation_e::Ship_shield_left, 5.f, 11, 0, 12, 0, 40, 45);
    animation_component_->AddAnimation(Animation_e::Ship_shield_right, 5.f, 13, 0, 14, 0, 40, 45);
    animation_component_->AddAnimation(Animation_e::Ship_explosion, 5.f, 0, 1, 21, 1, 40, 45);
}

/**
    Resets animation to default back from turning left or right
 */
//Functions
void Ship::ResetAnimationName()
{
    if (!shields_)
        animation_name_ = Animation_e::Ship_default;
    else
        animation_name_ = Animation_e::Ship_shield;
}

void Ship::Update(const float& delta, const sf::Vector2u& window_size)
{
    //If ship is exploding, stop movement, animate explosion, then alive = false
    if (exploding_)
    {
        if (animation_component_->Play(Animation_e::Ship_explosion, delta, true))
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
            shields_ = false;

        Entity::Update(delta, window_size);
    }
}

void Ship::Move(const float& dir_x, const float& dir_y, const float& delta)
{
    //Ship animation preset based on movement

    if (dir_x > 0 && !shields_)
        animation_name_ = Animation_e::Ship_default_right;
    else if (dir_x < 0 && !shields_)
        animation_name_ = Animation_e::Ship_default_left;
    else if (dir_x > 0 && shields_) 
        animation_name_ = Animation_e::Ship_shield_right;
    else if (dir_x < 0 && shields_) 
        animation_name_ = Animation_e::Ship_shield_left;
    else if (shields_)
        animation_name_ = Animation_e::Ship_shield;
    else
        animation_name_ = Animation_e::Ship_default;

    Entity::Move(dir_x, dir_y, delta);
}

void Ship::SetAlive(const bool& is_alive)
{
    exploding_ = true;
}

float Ship::GetAngle() const
{
    return sprite_.getRotation();
}
