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
    sf::RenderWindow*          window_;
    sf::Event                  event_;
    std::vector<sf::VideoMode> video_modes_;
    sf::ContextSettings        window_settings_;
    bool                       fullscreen_;

    sf::Clock clock_;
    float     delta_;

    std::stack<State*> states_;

    std::map<std::string, int> supported_keys_;

    //Inititalization
    void InitVariables();
    void InitWindow();
    void InitKeys();
    void InitStates();
};

#endif
