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

    int       Run();
    void      Quit();
    sf::Time& GetElapsed();
    void      RestartClock();

  private:
    void                mCreateWindow();
    sf::RenderWindow    mWindow;
    bool                mRunning;
    int                 mLives;
    sf::Clock           mClock;
    sf::Time            mElapsed;
};

#endif
