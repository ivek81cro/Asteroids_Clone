#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
        : font_(font)
{
    background_.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    background_.setFillColor(sf::Color(20, 20, 20, 100));

    container_.setSize(
        sf::Vector2f(static_cast<float>(vm.width / 4.f), static_cast<float>(vm.height)));
    container_.setFillColor(sf::Color(20, 20, 20, 200));
    container_.setPosition(
        static_cast<float>(vm.width / 2.f) - static_cast<float>(container_.getSize().x / 2.f), 0.f);

    menu_text_.setFont(font_);
    menu_text_.setFillColor(sf::Color(255, 255, 255, 200));
    menu_text_.setCharacterSize(gui::CalcFontSIze(vm));
    menu_text_.setString("PAUSED");
    menu_text_.setPosition(container_.getPosition().x + container_.getSize().x / 2.f -
                               menu_text_.getGlobalBounds().width / 2.f,
                           container_.getPosition().y + gui::PercToPixelY(5.56f, vm));
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

void PauseMenu::AddButton(const std::string key, const float y, const float width, const float height,
                          const unsigned char_size, const std::string text)
{
    float x = container_.getPosition().x + container_.getSize().x / 2.f - width / 2.f;

    buttons_[ key ] = new gui::Button(x, y, width, height, &font_, text, char_size, sf::Color(255, 0, 0, 200),
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
std::map<std::string, gui::Button*>& PauseMenu::GetButtons()
{
    return buttons_;
}
