#include "stdafx.h"
#include "DropLife.h"

/**
    Class for dropping extra life
 */
DropLife::DropLife(const float& x, const float& y, sf::Texture& texture_sheet, const float& scale)
        : lifetime_(5.f)
{
    scale_factor_   = scale;
    name_           = EntityName_e::Life;
    animation_name_ = Animation_e::Life_default;
    max_velocity_   = 50.f;
    alive_          = true;
    movement_name_  = Movement_e::Life;

    sprite_.setPosition(x, y);
    sprite_.setScale(scale_factor_, scale_factor_);
    sprite_.setRotation(static_cast<float>(rand() % 360));

    InitComponents(texture_sheet);
}

DropLife::~DropLife()
{
}

/**
    Update entity
 */
void DropLife::Update(const float& delta, const sf::Vector2u& window_size)
{
    //Remove drop if not picked up within 5 seconds
    lifetime_ -= delta;
    if (lifetime_ < 0)
    {
        alive_ = false;
    }
    Entity::Update(delta, window_size);
}

/**
    Initialize components needed for entity behaviour
 */
void DropLife::InitComponents(sf::Texture& texture_sheet)
{
    CreateAnimationComponent(texture_sheet);
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());
    CreateHitboxComponent(sprite_, 45 * scale_factor_);

    animation_component_->AddAnimation(animation_name_, 5.f, 0, 0, 7, 0, 45, 45);
}
