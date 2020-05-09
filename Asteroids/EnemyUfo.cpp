#include "stdafx.h"
#include "EnemyUfo.h"

EnemyUfo::EnemyUfo(float x, float y, sf::Texture& texture_sheet, float scale)
        : arriving_(true)
        , away_(false)
{
    scale_factor_ = scale;
    sprite_.setScale(scale_factor_, scale_factor_);
    sprite_.setPosition(x, y);

    name_ = "enemy_ufo";
    animation_name_ = name_;
    fire_cooldown_  = 5.f;
    lifetime_       = 10.f;

    InitComponents(texture_sheet);
}

EnemyUfo::~EnemyUfo()
{
}

//Functions
void EnemyUfo::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 45.f * scale_factor_);
    CreateAnimationComponent(texture_sheet);

    animation_component_->AddAnimation("enemy_ufo", 5.f, 0, 0, 11, 0, 48, 48);
    animation_component_->AddAnimation("enemy_ufo_active", 10.f, 12, 0, 17, 0, 48, 48);
    animation_component_->AddAnimation("enemy_ufo_away", 5.f, 11, 1, 17, 1, 48, 48);
}

void EnemyUfo::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (arriving_)
    {
        if (animation_component_->Play(animation_name_, delta, true))
        {
            arriving_       = false;
            animation_name_ = "enemy_ufo_active";
        }
    }
    if (away_)
    {
        if (animation_component_->Play(animation_name_, delta, true))
        {
            fire_cooldown_ = 20.f;
            away_          = false;
            alive_         = false;
        }
    }
    else
        animation_component_->Play(animation_name_, delta);

    std::cout << lifetime_ << std::endl;
}

const bool EnemyUfo::GetArriving() const
{
    return arriving_;
}

const float& EnemyUfo::GetFireCooldown() const
{
    return fire_cooldown_;
}

void EnemyUfo::ResetFireCooldown()
{
    fire_cooldown_ = 1.f;
}

void EnemyUfo::SetLifeTime(const float& delta)
{
    lifetime_ -= delta;
    fire_cooldown_ -= delta;
    if (lifetime_ < 0)
    {
        animation_name_ = "enemy_ufo_away";
        away_ = true;
    }
}

