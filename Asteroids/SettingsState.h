#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "State.h"
#include "Button.h"
#include "DropDownList.h"


class SettingsState : public State
{
  public:
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
    virtual ~SettingsState();

    //Accessor

    //Functions
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

    gui::DropDownList* ddl_;

    //Functions
    void InitVariables();
    void InitBackground();
    void InitFonts();
    void InitKeybinds();
    void InitButtons();
};

#endif // !SETTINGSSTATE_H_