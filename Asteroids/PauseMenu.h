#ifndef PAUSEMENU_H_
#define PAUSEMENU_H_

#include "Button.h"

class PauseMenu
{
  public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    //Functions
    const bool IsButtonPressed(const std::string key);
    void AddButton(const std::string key, float y, const std::string text);
    void Update(const sf::Vector2f& mouse_position);
    void Render(sf::RenderTarget& target);

    //Accessor
    std::map<std::string, gui::Button*>& GetButtons();

  private:
    sf::Font& font_;
    sf::Text  menu_text_;

    sf::RectangleShape background_;
    sf::RectangleShape container_;

    std::map<std::string, gui::Button*> buttons_;

    //Functions
};

#endif // !PAUSEMENU_H_
