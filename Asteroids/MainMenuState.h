#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "Button.h"
#include "GameState.h"

class MainMenuState : public State
{
  public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys);
    virtual ~MainMenuState();

    void EndState();

    void UpdateInput(const float& delta);
    void Update(const float& delta);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    sf::RectangleShape background_;
    sf::Font           font_;

    Button* game_state_button_;

    //Functions
    void InitFonts();
    void InitKeybinds();
};
#endif // !MAINMENUSTATE_H_
