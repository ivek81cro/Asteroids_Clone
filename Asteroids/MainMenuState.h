#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "Button.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"

class MainMenuState : public State
{
  public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void ResetGui();
    void UpdateInput(const float& delta);
    void UpdateButtons();
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    sf::RectangleShape background_;
    sf::Font           font_;

    std::map<std::string, gui::Button*> buttons_;

    sf::VideoMode current_vm_;

    //Functions
    void InitVariables();
    void InitFonts();
    void InitKeybinds();
    void InitGui();
};
#endif // !MAINMENUSTATE_H_
