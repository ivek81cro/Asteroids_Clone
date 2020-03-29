#ifndef _GAME_H_
#define _GAME_H_

#include "Bullet.h"
#include "Ship.h"
#include <SFML/Graphics.hpp>

class Game
{
  public:
    Game();
    ~Game();

    int       run();
    void      quit();
    sf::Time& GetElapsed();
    void      RestartClock();

  private:
    void                createWindow();
    sf::RenderWindow    window;
    bool                running;
    int                 lives;
    Ship                ship;
    std::vector<Bullet> bullets;
    sf::Clock           mClock;
    sf::Time            mElapsed;
};

#endif
