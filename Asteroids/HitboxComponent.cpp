#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float& width, float& factor)
        : sprite_(sprite)
        , factor_(factor)
{
    hitbox_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y);
    hitbox_.setRadius(width / 2.f * factor);
    hitbox_.setFillColor(sf::Color::Transparent);
    hitbox_.setOutlineThickness(1.f);
    hitbox_.setOutlineColor(sf::Color::Green);
    hitbox_.setOrigin(width / 2.f * factor_, width / 2.f * factor_);
}

HitboxComponent::~HitboxComponent()
{
}

//Functions
sf::CircleShape& HitboxComponent::GetHitbox()
{
    return hitbox_;
}

void HitboxComponent::Update()
{
    hitbox_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y);
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
    target.draw(hitbox_);
}
