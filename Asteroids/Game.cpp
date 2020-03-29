#include "Game.h"
#include "Constants.h"
#include "Level.h"

Game::Game()
        : running(true)
        , lives(3)
{
}

Game::~Game()
{
    window.close();
}

int Game::run()
{
    createWindow();

    Level       level;
    sf::Texture tBackground;
    tBackground.loadFromFile("images/background.jpg");
    sf::Sprite sBackground(tBackground);
    level.start();
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return EXIT_SUCCESS;
            }
            level.onEvent(event);
        }
        window.clear();
        window.draw(sBackground);
        RestartClock();
        level.update(GetElapsed().asMilliseconds(), event);
        level.show(window);
        window.display();
    }
    return EXIT_SUCCESS;
}

void Game::createWindow()
{
    if (window.isOpen())
        window.close();

    window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(W_FPSLIMIT);
}

void Game::RestartClock()
{
    mElapsed = mClock.restart();
}

sf::Time& Game::GetElapsed()
{
    return mElapsed;
}
