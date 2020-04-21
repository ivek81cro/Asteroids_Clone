#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width)
        : sprite_(sprite)
        , offset_x_(offset_x)
        , offset_y_(offset_y)
{
    hitbox_.setPosition(sprite_.getPosition().x + offset_x, sprite_.getPosition().y + offset_y);
    hitbox_.setRadius(width/2.f);
    hitbox_.setFillColor(sf::Color::Transparent);
    hitbox_.setOutlineThickness(1.f);
    hitbox_.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::CheckIntersect(const sf::FloatRect& frect)
{
    return hitbox_.getGlobalBounds().intersects(frect);       
}

void HitboxComponent::Update()
{
    hitbox_.setPosition(sprite_.getPosition().x + offset_x_, sprite_.getPosition().y + offset_y_);
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
    target.draw(hitbox_);
}
