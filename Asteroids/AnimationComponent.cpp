#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
        : sprite_(sprite)
        , texture_sheet_(texture_sheet)
{
}

AnimationComponent::~AnimationComponent()
{
    for (auto& i : animations_)
    {
        delete i.second;
    }
}

void AnimationComponent::AddAnimation(const std::string key, float animation_timer, int start_frame_x,
                                      int start_frame_y, int frames_x, int frames_y, int width, int height)
{
    animations_[ key ] = new Animation(sprite_, texture_sheet_, animation_timer, start_frame_x, start_frame_y, frames_x,
                                       frames_y, width, height);
}

//Functions
void AnimationComponent::Play(const std::string key, const float& delta)
{
    animations_[ key ]->Play(delta);
}
