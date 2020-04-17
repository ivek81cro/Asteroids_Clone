#ifndef PAUSEMENU_H_
#define PAUSEMENU_H_

#include "Button.h"
#include "SFML/Graphics.hpp"

class PauseMenu
{
  public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    //Functions
    void Update();
    void Render(sf::RenderTarget& target);

  private:
    sf::Font& font_;
    sf::Text  menu_text_;

    sf::RectangleShape background_;
    sf::RectangleShape container_;

    std::map<std::string, Button*> buttons_;
};

#endif // !PAUSEMENU_H_
