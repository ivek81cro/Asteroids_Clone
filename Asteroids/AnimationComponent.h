#ifndef ANIMATIONCOMPONENT_H_
#define ANIMATIONCOMPONENT_H_

#include <iostream>
#include <map>
#include <string>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class AnimationComponent
{
  private:
    class Animation
    {
      public:
        //Variables
        sf::Sprite&  sprite_;
        sf::Texture& texture_sheet_;
        float        animation_timer_;
        float        timer_;
        int          width_;
        int          height_;
        sf::IntRect  start_rect_;
        sf::IntRect  current_rect_;
        sf::IntRect  end_rect_;

        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer, int start_frame_x,
                  int start_frame_y, int frames_x, int frames_y, int width, int height)
                : sprite_(sprite)
                , texture_sheet_(texture_sheet)
                , width_(width)
                , height_(height)
                , animation_timer_(animation_timer)
        {
            timer_        = 0.f;
            start_rect_   = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            end_rect_     = sf::IntRect(frames_x * width, frames_y * height, width, height);
            current_rect_ = start_rect_;

            sprite_.setTexture(texture_sheet_, true);
            sprite_.setTextureRect(start_rect_);
            sprite_.setOrigin(width / 2.f, height / 2.f);
        }

        //Functions
        void Play(const float& delta)
        {
            //Update timer
            timer_ += 100.f * delta;
            if (timer_ >= animation_timer_)
            {
                //Reset timer
                timer_ = 0.f;

                //Animate
                if (current_rect_ != end_rect_)
                {
                    current_rect_.left += width_;
                }
                else //Reset
                {
                    current_rect_.left = start_rect_.left;
                }
                sprite_.setTextureRect(current_rect_);
            }
        }

        void Reset()
        {
            timer_        = animation_timer_;
            current_rect_ = start_rect_;
        }
    };

  public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    //Functions
    void AddAnimation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x,
                      int frames_y, int width, int height);

    void Play(const std::string key, const float& delta);

  private:
    std::map<std::string, Animation*> animations_;

    Animation* last_animation_;

    sf::Sprite&  sprite_;
    sf::Texture& texture_sheet_;
};

#endif
