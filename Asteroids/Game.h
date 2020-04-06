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

    //Regular
    void EndApplication();

    //Update
    void UpdateDelta();
    void UpdateSFMLEvents();
    void Update();

    //Render
    void Render();

    //Core
    int Run();

  private:
    sf::RenderWindow* window_;
    sf::Event         event_;

    sf::Clock clock_;
    float     delta_;

    std::stack<State*> states_;

    std::map<std::string, int> supported_keys_;

     //Inititalization
    void InitWindow();
    void InitKeys();
    void InitStates();
};

#endif
