#ifndef PAUSEMENU_H_
#define PAUSEMENU_H_

#include "Button.h"
#include "State.h"

class PauseMenu
{
  public:
    PauseMenu(sf::VideoMode& vm, sf::Font& font, ButtonSettings& btn_settings);
    virtual ~PauseMenu();

    //Functions
    const bool IsButtonPressed(const Buttons key);
    void       AddButton(const Buttons key, const float y, const float width, const float height,
                         const unsigned char_size, const std::string text);
    void       Update(const sf::Vector2f& mouse_position);
    void       Render(sf::RenderTarget& target);

    //Accessor
    std::map<Buttons, std::unique_ptr<gui::Button>>& GetButtons();

  private:
    sf::Font&          font_;
    sf::Text           menu_text_;
    sf::RectangleShape background_;
    sf::RectangleShape container_;

    ButtonSettings* btn_settings_;

    std::map<Buttons, std::unique_ptr<gui::Button>> buttons_;

    //Functions
};

#endif // !PAUSEMENU_H_
