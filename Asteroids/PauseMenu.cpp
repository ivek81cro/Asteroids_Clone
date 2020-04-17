#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
        : font_(font)
{
    background_.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    background_.setFillColor(sf::Color(20, 20, 20, 100));

    container_.setSize(
        sf::Vector2f(static_cast<float>(window.getSize().x / 4.f), static_cast<float>(window.getSize().y)));
    container_.setFillColor(sf::Color(20, 20, 20, 200));
    container_.setPosition(
        static_cast<float>(window.getSize().x / 2.f) - static_cast<float>(container_.getSize().x / 2.f), 0.f);

    menu_text_.setFont(font_);
    menu_text_.setFillColor(sf::Color(255, 255, 255, 200));
    menu_text_.setCharacterSize(60);
    menu_text_.setString("PAUSED");
    menu_text_.setPosition(container_.getPosition().x + container_.getSize().x / 2.f -
                               menu_text_.getGlobalBounds().width / 2.f,
                           container_.getPosition().y + 40.f);
}

PauseMenu::~PauseMenu()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
}


//Functions
const bool PauseMenu::IsButtonPressed(const std::string key)
{
    return buttons_[ key ]->IsPressed();
}

void PauseMenu::AddButton(const std::string key, float y, const std::string text)
{
    float width     = 250.f;
    float height    = 50.f;
    float x         = container_.getPosition().x + container_.getSize().x / 2.f - width / 2.f;

    buttons_[ key ] = new Button(x, y, width, height, &font_, text, 50, sf::Color(255, 0, 0, 200),
                                 sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50), sf::Color(255, 0, 0, 0),
                                 sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));
}

void PauseMenu::Update(const sf::Vector2f& mouse_position)
{
    for (auto& i : buttons_)
    {
        i.second->Update(mouse_position);
    }
}

void PauseMenu::Render(sf::RenderTarget& target)
{
    target.draw(background_);
    target.draw(container_);

    for (auto& i : buttons_)
    {
        i.second->Render(target);
    }

    target.draw(menu_text_);
}

//Accessor
std::map<std::string, Button*>& PauseMenu::GetButtons()
{
    return buttons_;
}
