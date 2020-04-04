#ifndef _GAME_H_
#define _GAME_H_

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
    void endApplication();

    //Update
    void updateDelta();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    int run();

  private:
    sf::RenderWindow* window;
    sf::Event         event;

    sf::Clock clock;
    float     delta;

    std::stack<State*> states;

    bool                running;
    int                 lives;
    Ship                ship;
    std::vector<Bullet> bullets;

    //Inititalization
    void initWindow();
    void initStates();
};

#endif
