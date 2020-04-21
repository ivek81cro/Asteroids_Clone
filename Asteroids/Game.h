#ifndef GAME_H_
#define GAME_H_

#include "MainMenuState.h"

class Game
{
  public:
    //Constructors/Destructors
    Game();
    virtual ~Game();

    //Functions

    //Regular functions
    void EndApplication();

    //Update
    void UpdateDelta();
    void UpdateSFMLEvents();
    void Update();

    //Render functions
    void Render();

    //Core function
    int Run();

  private:
    GraphicsSettings           gfx_settings_;
    sf::RenderWindow*          window_;
    sf::Event                  event_;

    sf::Clock clock_;
    float     delta_;

    std::stack<State*> states_;

    std::map<std::string, int> supported_keys_;

    //Inititalization
    void InitVariables();
    void InitGraphicsSettings();
    void InitWindow();
    void InitKeys();
    void InitStates();
};

#endif
