#include "stdafx.h"
#include "AnimationComponent.h"

/**
    Class for animating sprites
 */
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
        : sprite_(sprite)
        , texture_sheet_(texture_sheet)
        , last_animation_(nullptr)
        , prority_animation_(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
}

/**
    Return if animation ran all frames 'till last
 */
//Accessor
const bool& AnimationComponent::IsDone(const std::string key)
{
    return animations_[ key ]->IsDone();
}

/**
    Add spritesheet with number of frames for animation
 */
//Functions
void AnimationComponent::AddAnimation(const std::string key, float animation_timer, int start_frame_x,
                                      int start_frame_y, int frames_x, int frames_y, int width, int height)
{
    animations_[ key ] = std::unique_ptr<Animation>(new Animation(sprite_, texture_sheet_, animation_timer, start_frame_x, start_frame_y, frames_x,
                                       frames_y, width, height));
}

/**
    Play animation, if there are multiple, one can be prioritized
 */
const bool& AnimationComponent::Play(const std::string key, const float& delta, const bool priority)
{
    if (prority_animation_)//If exists priority animation
    {
        if (prority_animation_ == animations_[ key ].get())
        {
            if (last_animation_ != animations_[ key ].get() && last_animation_ != nullptr)
            {
                if (last_animation_ == nullptr)
                    last_animation_ = animations_[ key ].get();
                else
                {
                    last_animation_->Reset();
                    last_animation_ = animations_[ key ].get();
                }
            }
            if (animations_[ key ]->Play(delta))
            {
                prority_animation_ = nullptr;
            }
        }
    }
    else
    {
        if (priority)//If this is priority animation 
        {
            prority_animation_ = animations_[ key ].get();
        }
        if (last_animation_ != animations_[ key ].get() && last_animation_ != nullptr)
        {
            if (last_animation_ == nullptr)
                last_animation_ = animations_[ key ].get();
            else
            {
                last_animation_->Reset();
                last_animation_ = animations_[ key ].get();
            }
        }
        animations_[ key ]->Play(delta);
    }
    return animations_[ key ]->IsDone();
}
