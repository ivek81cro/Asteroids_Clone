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
    void Run();

  private:
    GraphicsSettings                  gfx_settings_;
    StateData                         state_data_;
    std::unique_ptr<sf::RenderWindow> window_;
    sf::Event                         event_;

    sf::Clock clock_;
    float     delta_;

    std::stack<std::unique_ptr<State>> states_;

    std::map<SupportedKey_e, int> supported_keys_;

    //Inititalization
    void InitVariables();
    void InitGraphicsSettings();
    void InitWindow();
    void InitKeys();
    void InitStateData();
    void InitStates();

    SupportedKey_e SelectEnum(std::string key);
};

#endif
