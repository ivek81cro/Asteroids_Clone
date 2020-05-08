#include "stdafx.h"
#include "Ship.h"

//Constructors / Destructors
Ship::Ship(float x, float y, sf::Texture& texture_sheet, int lives, float scale)
        : lives_(lives)
        , shield_timer_(3.f)
        , invulnerability_(true)
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
    name_           = "ship";
    animation_name_ = "ship_sh";
    max_velocity_   = 200.f * scale_factor_;
    acceleration_   = 400.f * scale_factor_;
}

void Ship::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 38.f * scale_factor_);
    CreateMovementComponent(max_velocity_, acceleration_, 0.998f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation("ship", 8.f, 1, 0, 2, 0, 40, 45);
    animation_component_->AddAnimation("ship_l", 5.f, 4, 0, 5, 0, 40, 45);
    animation_component_->AddAnimation("ship_r", 5.f, 7, 0, 8, 0, 40, 45);
    animation_component_->AddAnimation("ship_sh", 8.f, 9, 0, 10, 0, 40, 45);
    animation_component_->AddAnimation("ship_l_sh", 5.f, 11, 0, 12, 0, 40, 45);
    animation_component_->AddAnimation("ship_r_sh", 5.f, 13, 0, 14, 0, 40, 45);
    animation_component_->AddAnimation("ship_explode", 5.f, 0, 1, 21, 1, 40, 45);
}

//Functions
void Ship::ResetAnimationName()
{
    if (!invulnerability_)
        animation_name_ = name_;
    else
        animation_name_ = "ship_sh";
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
    //Ship animation preset based on movement

    if (dir_x > 0 && !invulnerability_)
        animation_name_ = "ship_r";
    else if (dir_x < 0 && !invulnerability_)
        animation_name_ = "ship_l";
    else if(dir_x > 0 && invulnerability_) 
        animation_name_ = "ship_r_sh";
    else if (dir_x < 0 && invulnerability_) 
        animation_name_ = "ship_l_sh";
    else if (invulnerability_)
        animation_name_ = "ship_sh";
    else
        animation_name_ = name_;

    Entity::Move(dir_x, dir_y, delta);
}

void Ship::SetAlive(bool is_alive)
{
    exploding_ = true;
}

bool Ship::ShieldsUp()
{
    return invulnerability_;
}

const int& Ship::GetLivesRemaining() const
{
    return lives_;
}

float Ship::GetAngle() const
{
    return sprite_.getRotation();
}
