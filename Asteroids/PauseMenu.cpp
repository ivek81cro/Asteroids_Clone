#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
        : font_(font)
{
    background_.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    background_.setFillColor(sf::Color(20, 20, 20, 100));

    container_.setSize(sf::Vector2f(static_cast<float>(window.getSize().x / 4.f), static_cast<float>(window.getSize().y)));
    container_.setFillColor(sf::Color(20, 20, 20, 200));
    container_.setPosition(static_cast<float>(window.getSize().x / 2.f) - static_cast<float>(container_.getSize().x / 2.f), 0.f);

    menu_text_.setFont(font_);
    menu_text_.setFillColor(sf::Color(255, 255, 255, 200));
    menu_text_.setCharacterSize(60);
    menu_text_.setString("PAUSED");
    menu_text_.setPosition(container_.getPosition().x + container_.getSize().x / 2.f - menu_text_.getGlobalBounds().width / 2.f, 
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
void PauseMenu::Update()
{
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
