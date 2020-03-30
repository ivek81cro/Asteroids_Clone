#include "Game.h"
#include "Constants.h"
#include "Level.h"

Game::Game()
        : mRunning(true)
        , mLives(3)
{
}

Game::~Game()
{
    mWindow.close();
}

int Game::run()
{
    mCreateWindow();

    Level       level;
    sf::Texture tBackground;
    tBackground.loadFromFile("images/background.jpg");
    sf::Sprite sBackground(tBackground);
    level.start();
    while (mRunning)
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
                return EXIT_SUCCESS;
            }
            level.onEvent(event);
        }
        mWindow.clear();
        mWindow.draw(sBackground);
        RestartClock();
        level.update(GetElapsed(), event);
        level.show(mWindow);
        mWindow.display();
    }
    return EXIT_SUCCESS;
}

void Game::mCreateWindow()
{
    if (mWindow.isOpen())
        mWindow.close();

    mWindow.create(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Close);
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(W_FPSLIMIT);
}

void Game::RestartClock()
{
    mElapsed = mClock.restart();
}

sf::Time& Game::GetElapsed()
{
    return mElapsed;
}
