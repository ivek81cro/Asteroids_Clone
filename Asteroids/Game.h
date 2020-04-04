#ifndef GAME_H_
#define GAME_H_

#include "Bullet.h"
#include "GameState.h"
#include "Level.h"
#include "Ship.h"

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

    bool                running_;
    int                 lives_;
    Ship                ship_;
    std::vector<Bullet> bullets_;

    //Inititalization
    void InitWindow();
    void InitStates();
};

#endif
