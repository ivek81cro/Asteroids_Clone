#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "State.h"
#include "Button.h"
#include "DropDownList.h"


class SettingsState : public State
{
  public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Accessor

    //Functions
    void UpdateInput(const float& delta);
    void UpdateGui(const float& delta);
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    sf::RectangleShape background_;
    sf::Font           font_;

    std::map<std::string, gui::Button*> buttons_;
    std::map<std::string, gui::DropDownList*> ddl_;

    sf::Text options_text_;
    sf::Text warning_text_;

    std::vector<sf::VideoMode> v_modes_;

    //Functions
    void InitVariables();
    void InitFonts();
    void InitKeybinds();
    void InitGui();
    void InitBackground(const sf::VideoMode& vm);
    void InitButtons(const sf::VideoMode& vm);
    void InitDropdownList(const sf::VideoMode& vm);
    void InitText(const sf::VideoMode& vm);
    void ResetGui();
};

#endif // !SETTINGSSTATE_H_