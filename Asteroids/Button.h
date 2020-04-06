#ifndef BUTTON_H_
#define BUTTON_H_

#include "SFML/Graphics.hpp"

enum button_states
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button
{
  public:
    Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idle_color,
           sf::Color hover_color, sf::Color active_color);
    virtual ~Button();

    //Accessors
    const bool IsPressed() const;

    //Functions
    void Update(sf::Vector2f mouse_pos);
    void Render(sf::RenderTarget* target);

  private:
    short unsigned button_state_;

    sf::RectangleShape shape_;
    sf::Font*          font_;
    sf::Text           text_;

    sf::Color idle_color_;
    sf::Color hover_color_;
    sf::Color active_color_;
};

#endif // !BUTTON_H_
