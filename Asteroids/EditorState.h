#ifndef EDITORSTATE_H_
#define EDITORSTATE_H_

#include "State.h"
#include "Button.h"

class EditorState : public State
{
  public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
    virtual ~EditorState();

    void UpdateInput(const float& delta);
    void UpdateButtons();
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget* target = nullptr);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    //Variables
    sf::Font           font_;

    std::map<std::string, Button*> buttons_;

    //Functions
    void InitVariables();
    void InitBackground();
    void InitFonts();
    void InitKeybinds();
    void InitButtons();
};

#endif