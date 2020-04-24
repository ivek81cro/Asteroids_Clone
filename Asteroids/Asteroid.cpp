#include "stdafx.h"
#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, int level, sf::Texture& texture_sheet)
        : level_(level)
{
    SetPosition(x, y);

    InitVariables();
    InitComponents();
    
    SetScale(level);

    CreateHitboxComponent(sprite_, 42, factor_);
    CreateMovementComponent(max_velocity_asteroid_, 0.f, 0.f, sprite_.getRotation());
    CreateAnimationComponent(texture_sheet);    

    animation_component_->AddAnimation(name_, 5.f, 0, 0, 15, 0, 64, 64);
    animation_component_->AddAnimation("asteroid_explode", 5.f, 0, 1, 64, 1, 64, 64);
}

Asteroid::~Asteroid()
{
}

//Functions
void Asteroid::SetScale(const int& level)
{
    factor_ = 1.f;
    if (level == 2)
    {
        factor_                = 0.75f;
        max_velocity_asteroid_ = 100.f;
    }
    if (level == 3)
    {

        factor_ = 0.5f;
        max_velocity_asteroid_ = 150.f;
    }

    sprite_.setScale(factor_, factor_);
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

//Initializer functions
void Asteroid::InitVariables()
{
    name_  = "asteroid";
    animation_name_ = name_;
    sprite_.setRotation(static_cast<float>((rand() % 360)));
    max_velocity_asteroid_ = 50.f;
}

void Asteroid::InitComponents()
{
}
