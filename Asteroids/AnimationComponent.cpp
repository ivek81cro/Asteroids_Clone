#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
        : sprite_(sprite)
        , texture_sheet_(texture_sheet)
{
}

AnimationComponent::~AnimationComponent()
{
}

//Functions
void AnimationComponent::Update(const float& delta)
{
}

