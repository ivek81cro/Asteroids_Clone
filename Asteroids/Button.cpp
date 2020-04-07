#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idle_color,
               sf::Color hover_color, sf::Color active_color)
{
    button_state_ = BTN_IDLE;

    shape_.setPosition(sf::Vector2f(x, y));
    shape_.setSize(sf::Vector2f(width, height));

    font_ = font;
    text_.setFont(*font);
    text_.setString(text);
    text_.setFillColor(sf::Color::White);
    text_.setCharacterSize(16);
    text_.setOutlineThickness(2);
    text_.setPosition(
        shape_.getPosition().x + (shape_.getGlobalBounds().width / 2.f) - text_.getGlobalBounds().width / 2.f,
        shape_.getPosition().y + (shape_.getGlobalBounds().height / 2.f) - text_.getGlobalBounds().height / 2.f
    );

    idle_color_   = idle_color;
    hover_color_  = hover_color;
    active_color_ = active_color;

    shape_.setFillColor(idle_color);
}

Button::~Button()
{
}

const bool Button::IsPressed() const
{
    if (button_state_ == BTN_ACTIVE)
        return true;

    return false;
}

void Button::Update(sf::Vector2f mouse_pos)
{
    button_state_ = BTN_IDLE;
    if (shape_.getGlobalBounds().contains(mouse_pos))
    {
        button_state_ = BTN_HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            button_state_ = BTN_ACTIVE;
        }
    }

    switch (button_state_)
    {
        case BTN_IDLE: 
            shape_.setFillColor(idle_color_);
            break;
        case BTN_HOVER: shape_.setFillColor(hover_color_);
            break;
        case BTN_ACTIVE: shape_.setFillColor(active_color_);
            break;
        default: 
            shape_.setFillColor(sf::Color::Red);
            break;
    }
}

void Button::Render(sf::RenderTarget* target)
{
    target->draw(shape_);
    target->draw(text_);
}
