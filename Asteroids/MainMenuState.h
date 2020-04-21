#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "Button.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"

class MainMenuState : public State
{
  public:
    MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfx_settings, std::map<std::string, int>* supported_keys,
                  std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void UpdateInput(const float& delta);
    void UpdateButtons();
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    GraphicsSettings&  gfx_settings_;
    sf::RectangleShape background_;
    sf::Font           font_;

    std::map<std::string, gui::Button*> buttons_;

    //Functions
    void InitVariables();
    void InitBackground();
    void InitFonts();
    void InitKeybinds();
    void InitButtons();
};
#endif // !MAINMENUSTATE_H_
