#ifndef EDITORSTATE_H_
#define EDITORSTATE_H_

#include "State.h"
#include "Button.h"

class EditorState : public State
{
  public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    void UpdateInput(const float& delta);
    void UpdateButtons();
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    sf::Font           font_;

    std::map<std::string, gui::Button*> buttons_;

    //Functions
    void InitVariables();
    void InitBackground();
    void InitFonts();
    void InitKeybinds();
    void InitButtons();
};

#endif