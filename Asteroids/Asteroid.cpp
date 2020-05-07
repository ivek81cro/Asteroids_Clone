#include "stdafx.h"
#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, int level, sf::Texture& texture_sheet, float scale_factor, float& game_level)
        : level_(level)
{
    game_level_   = game_level;
    scale_factor_ = scale_factor;

    SetPosition(x, y);
    InitVariables();
    SetScale(level);
    InitComponents(texture_sheet);
    SetScale(level);
}

Asteroid::~Asteroid()
{
}

void Asteroid::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 42, rescale_factor_);
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation(name_, 5.f, 0, 0, 15, 0, 64, 64);
    animation_component_->AddAnimation("asteroid_explode", 5.f, 0, 1, 64, 1, 64, 64);
}

//Initializer functions
void Asteroid::InitVariables()
{
    name_           = "asteroid";
    animation_name_ = name_;
    max_velocity_   = 50.f * scale_factor_ * game_level_;

    sprite_.setScale(scale_factor_, scale_factor_);
    sprite_.setRotation(static_cast<float>((rand() % 360)));

    switch (level_)
    {
        case 1: 
            points_ = 10; 
            break;
        case 2: 
            points_ = 20; 
            break;
        case 3: 
            points_ = 30; 
            break;
        default: 
            break;
    }
}

//Functions
void Asteroid::SetScale(const int& level)
{
    rescale_factor_ = scale_factor_;
    if (level == 2)
    {
        rescale_factor_        *= 0.75f;
        max_velocity_ = scale_factor_ * 75.f * game_level_;
    }
    if (level == 3)
    {
        rescale_factor_        *= 0.5f;
        max_velocity_ = scale_factor_ * 100.f * game_level_;
    }

    sprite_.setScale(rescale_factor_, rescale_factor_);
}

void Asteroid::SetAlive(bool is_alive)
{
    exploding_ = true;
}

void Asteroid::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (level_ > 3)
        alive_ = false;

    if (exploding_)
    {
        if (animation_component_->Play("asteroid_explode", delta, true))
        {
            exploding_ = false;
            alive_     = false;
        }
    }
    else
        Entity::Update(delta, window_size);
}

const int& Asteroid::GetLevel() const
{
    return level_;
}

const sf::Vector2f& Asteroid::Getposition() const
{
    return sprite_.getPosition();
}

const int Asteroid::GetPoints() const
{
    return points_;
}

