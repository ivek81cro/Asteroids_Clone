#include "Button.h"

//Constructors / Destructors
Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color ,sf::Color idle_color,
               sf::Color hover_color, sf::Color active_color)
{
    button_state_ = BTN_IDLE;

    shape_.setPosition(sf::Vector2f(x, y));
    shape_.setSize(sf::Vector2f(width, height));
    shape_.setFillColor(idle_color);

    font_ = font;
    text_.setFont(*font);
    text_.setString(text);
    text_.setFillColor(text_idle_color);
    text_.setCharacterSize(character_size);
    text_.setOutlineThickness(2);
    text_.setPosition(
        shape_.getPosition().x + (shape_.getGlobalBounds().width / 2.f) - text_.getGlobalBounds().width / 2.f,
        shape_.getPosition().y + (shape_.getGlobalBounds().height / 2.f) - text_.getGlobalBounds().height / 2.f
    );

    text_idle_color_ = text_idle_color;
    text_hover_color_ = text_hover_color;
    text_active_color_ = text_active_color;

    idle_color_   = idle_color;
    hover_color_  = hover_color;
    active_color_ = active_color;
}

Button::~Button()
{
}

//Accessors
const bool Button::IsPressed() const
{
    if (button_state_ == BTN_ACTIVE)
        return true;

    return false;
}

//Functions
void Button::Update(const sf::Vector2f& mouse_pos)
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
            text_.setFillColor(text_idle_color_);
            break;
        case BTN_HOVER: 
            shape_.setFillColor(hover_color_);
            text_.setFillColor(text_hover_color_);
            break;
        case BTN_ACTIVE: 
            shape_.setFillColor(active_color_);
            text_.setFillColor(text_active_color_);
            break;
        default: 
            shape_.setFillColor(sf::Color::Red);
            text_.setFillColor(sf::Color::Blue);
            break;
    }
}

void Button::Render(sf::RenderTarget& target)
{
    target.draw(shape_);
    target.draw(text_);
}
