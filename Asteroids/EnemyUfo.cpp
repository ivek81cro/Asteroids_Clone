#include "stdafx.h"
#include "EnemyUfo.h"

EnemyUfo::EnemyUfo(float x, float y, sf::Texture& texture_sheet, float scale, int& game_level)
        : away_(false)
        , points_(40)
        , lifetime_(6.f)
{
    scale_factor_ = scale;
    sprite_.setScale(scale_factor_, scale_factor_);
    sprite_.setPosition(x, y);
    sprite_.setRotation(static_cast<float>((rand() % 360)));

    game_level_ = static_cast<float>(game_level);

    InitVariables();
    InitComponents(texture_sheet);
}

EnemyUfo::~EnemyUfo()
{
}

/**
    Initialize components needed for entity behaviour
 */
//Functions
void EnemyUfo::InitComponents(sf::Texture& texture_sheet)
{
    CreateHitboxComponent(sprite_, 45.f * scale_factor_);
    CreateAnimationComponent(texture_sheet);
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());

    animation_component_->AddAnimation(Animation_e::Enemy_ufo_default, 3.f, 0, 0, 17, 0, 48, 48);
    animation_component_->AddAnimation(Animation_e::Enemy_ufo_active, 3.f, 0, 1, 5, 1, 48, 48);
    animation_component_->AddAnimation(Animation_e::Enemy_ufo_away, 3.f, 0, 1, 17, 1, 48, 48);
    animation_component_->AddAnimation(Animation_e::Enemy_ufo_explosion, 5.f, 0, 2, 16, 2, 48, 48);
}

void EnemyUfo::InitVariables()
{
    name_           = EntityName_e::Enemy_ufo;
    animation_name_ = Animation_e::Enemy_ufo_default;
    exploding_      = false;
    max_velocity_   = 100.f * game_level_ / 2;
    movement_name_  = Movement_e::Enemy_ufo;
    shields_        = true;
}

/**
    Update entity based on state (arriving, active, going away)
 */
void EnemyUfo::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (shields_ && !away_)
    {
        if (animation_component_->Play(animation_name_, delta, true))
        {
            shields_ = false;
            animation_name_   = Animation_e::Enemy_ufo_active;
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
    SetLifeTime(delta);
}

void EnemyUfo::SetLifeTime(const float& delta)
{
    if (!shields_)
    {
        lifetime_ -= delta;
    }

    if (lifetime_ < 0)
    {
        animation_name_   = Animation_e::Enemy_ufo_away;
        away_             = true;
        shields_ = true;
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
        animation_name_ = Animation_e::Enemy_ufo_explosion;
    }
}

