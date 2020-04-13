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

        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer, int start_x, int start_y,
                  int end_x, int end_y, int width, int height)
                : sprite_(sprite)
                , texture_sheet_(texture_sheet)
                , width_(width)
                , height_(height)
                , animation_timer_(animation_timer)
        {
            start_rect_   = sf::IntRect(start_x, start_y, width, height);
            end_rect_     = sf::IntRect(end_x, end_y, width, height);
            current_rect_ = start_rect_;

            sprite_.setTexture(texture_sheet_, true);
            sprite_.setTextureRect(start_rect_);
        }

        //Functions
        void Update(const float& delta)
        {
            //Update timer
            timer_ = 10.f;
            if (timer_ >= animation_timer_)
            {
                //Reset timer
                timer_ = 0.f;

                //Animate
                if (start_rect_ != end_rect_)
                {
                    current_rect_.left += width_;
                }
                else //Reset
                {
                    current_rect_.left = start_rect_.left;
                }
            }
        }

        void Pause();
        void Reset();
    };

  public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    //Functions
    void AddAnimation(const std::string key);

    void StartAnimation(std::string animation);
    void PauseAnimation(std::string animation);
    void ResetAnimation(std::string animation);

    void Update(const float& delta);

  private:
    std::map<std::string, Animation> animations_;

    sf::Sprite&  sprite_;
    sf::Texture& texture_sheet_;
};

#endif
