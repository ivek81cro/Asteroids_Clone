#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "Button.h"
#include "GameState.h"

class MainMenuState : public State
{
  public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
    virtual ~MainMenuState();

    void UpdateInput(const float& delta);
    void UpdateButtons();
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget* target = nullptr);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    sf::Texture        background_texture_;
    sf::RectangleShape background_;
    sf::Font           font_;

    std::map<std::string, Button*> buttons_;

    //Functions
    void InitVariables();
    void InitBackground();
    void InitFonts();
    void InitKeybinds();
    void InitButtons();
};
#endif // !MAINMENUSTATE_H_
