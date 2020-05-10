#include "stdafx.h"
#include "DropLife.h"

DropLife::DropLife(float x, float y, sf::Texture& texture_sheet, float scale)
        : lifetime_(5.f)
{
    scale_factor_ = scale;
    name_         = "life";
    animation_name_ = name_;
    max_velocity_   = 50.f;
    alive_          = true;

    sprite_.setPosition(x, y);
    sprite_.setScale(scale_factor_, scale_factor_);
    sprite_.setRotation(static_cast<float>(rand() % 360));

    InitComponents(texture_sheet);
    
}

DropLife::~DropLife()
{
}

void DropLife::Update(const float& delta, const sf::Vector2u& window_size)
{
    lifetime_ -= delta;
    if ( lifetime_ < 0)
    {
        alive_ = false;
    }
    Entity::Update(delta, window_size);
}

void DropLife::InitComponents(sf::Texture& texture_sheet)
{
    CreateAnimationComponent(texture_sheet);
    CreateMovementComponent(max_velocity_, 0.f, 0.f, sprite_.getRotation());
    CreateHitboxComponent(sprite_, 45 * scale_factor_);

    animation_component_->AddAnimation("life", 5.f, 0, 0, 7, 0, 45, 45);
}
