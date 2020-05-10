#include "stdafx.h"
#include "EnemyUfo.h"

EnemyUfo::EnemyUfo(float x, float y, sf::Texture& texture_sheet, float scale, int& game_level)
        : invoulnerability_(true)
        , away_(false)
        , points_(40)
        , lifetime_(6.f)
        , fire_cooldown_(1.5f)
{
    scale_factor_ = scale;
    sprite_.setScale(scale_factor_, scale_factor_);
    sprite_.setPosition(x, y);

    name_ = "enemy_ufo";
    game_level_     = static_cast<float>(game_level);
    animation_name_ = name_;
    exploding_      = false;
    max_velocity_   = 100.f * game_level_ / 2;
    sprite_.setRotation(static_cast<float>((rand() % 360)));

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
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());

    animation_component_->AddAnimation("enemy_ufo", 3.f, 0, 0, 17, 0, 48, 48);
    animation_component_->AddAnimation("enemy_ufo_active", 3.f, 0, 1, 5, 1, 48, 48);
    animation_component_->AddAnimation("enemy_ufo_away", 3.f, 0, 1, 17, 1, 48, 48);
    animation_component_->AddAnimation("enemy_ufo_exploding", 5.f, 0, 2, 16, 2, 48, 48);
}

void EnemyUfo::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (invoulnerability_ && !away_)
    {
        if (animation_component_->Play(animation_name_, delta, true))
        {
            invoulnerability_ = false;
            animation_name_   = "enemy_ufo_active";
        }
    }
    else if (away_)
    {
        if (animation_component_->Play(animation_name_, delta, true))
        {
            away_  = false;
            alive_ = false;
        }
    }
    else if (exploding_)
    {
        if (animation_component_->Play(animation_name_, delta, true))
        {
            alive_ = false;
        }
    }
    else
    {
        movement_component_->Update(delta, window_size);
        animation_component_->Play(animation_name_, delta);
    }

    hitbox_component_->Update();

    std::cout << lifetime_ << std::endl;
}

const bool EnemyUfo::GetInvoulnerability() const
{
    return invoulnerability_;
}

const float& EnemyUfo::GetFireCooldown() const
{
    return fire_cooldown_;
}

void EnemyUfo::ResetFireCooldown()
{
    fire_cooldown_ = 1.5f;
}

void EnemyUfo::SetLifeTime(const float& delta)
{
    if (!invoulnerability_)
    {
        lifetime_ -= delta;
        fire_cooldown_ -= delta;
    }

    if (lifetime_ < 0)
    {
        animation_name_   = "enemy_ufo_away";
        away_             = true;
        invoulnerability_ = true;
    }
}

const int EnemyUfo::GetPoints() const
{
    return points_;
}

void EnemyUfo::SetAlive(bool is_alive)
{
    if (!is_alive)
    {
        exploding_      = true;
        fire_cooldown_  = 20.f;
        animation_name_ = "enemy_ufo_exploding";
    }
}

