#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font, ButtonSettings& btn_settings)
        : font_(font)
        , btn_settings_(&btn_settings)
{
    background_.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    background_.setFillColor(sf::Color(20, 20, 20, 100));

    container_.setSize(
        sf::Vector2f(static_cast<float>(vm.width / 4.f), static_cast<float>(vm.height)));
    container_.setFillColor(btn_settings_->btn_ddl_bg_active_);
    container_.setPosition(
        static_cast<float>(vm.width / 2.f) - static_cast<float>(container_.getSize().x / 2.f), 0.f);

    menu_text_.setFont(font_);
    menu_text_.setFillColor(sf::Color(255, 255, 255, 200));
    menu_text_.setCharacterSize(gui::CalcFontSize(vm, 40));
    menu_text_.setString("PAUSED");
    menu_text_.setPosition(container_.getPosition().x + container_.getSize().x / 2.f -
                               menu_text_.getGlobalBounds().width / 2.f,
                           container_.getPosition().y + gui::PercToPixelY(5.56f, vm));
}

PauseMenu::~PauseMenu()
{
}

//Functions
const bool PauseMenu::IsButtonPressed(const Buttons key)
{
    return buttons_[ key ]->IsPressed();
}


/**
    Adds button to pause screen
 */
void PauseMenu::AddButton(const Buttons key, const float y, const float width, const float height,
                          const unsigned char_size, const std::string text)
{
    float x = container_.getPosition().x + container_.getSize().x / 2.f - width / 2.f;

    buttons_[ key ] = std::unique_ptr<gui::Button>(new gui::Button(x, y, width, height, &font_, text, char_size, btn_settings_->btn_txt_idle_,
                        btn_settings_->btn_txt_hover_, btn_settings_->btn_txt_active_,
                        btn_settings_->btn_bg_idle_, btn_settings_->btn_bg_hover_,
                        btn_settings_->btn_bg_active_));
}


/**
    Update and check buttons
 */
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
std::map<Buttons, std::unique_ptr<gui::Button>>& PauseMenu::GetButtons()
{
    return buttons_;
}
