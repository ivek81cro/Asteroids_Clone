#include "Game.h"
#include "Constants.h"
#include "Level.h"

//Initialization
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    sf::VideoMode windowBounds(800, 600);
    std::string   title;
    unsigned      frameRateLimit = 120;
    bool          vSyncEnabled   = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> frameRateLimit;
        ifs >> vSyncEnabled;
    }

    ifs.close();

    window = new sf::RenderWindow(windowBounds, title);
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(frameRateLimit);
    window->setVerticalSyncEnabled(vSyncEnabled);
}

void Game::initStates()
{
    states.push(new GameState(window));
}

//Constructors/Destructors
Game::Game()
{
    initWindow();
    initStates();
}

Game::~Game()
{
    delete window;

    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

//Regular
void Game::endApplication()
{

}

//Update
void Game::updateDelta()
{
    delta = clock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Game::update()
{
    updateSFMLEvents();

    if (!states.empty())
    {
        states.top()->update(delta);

        if (states.top()->getQuit())
        {
            states.top()->endState();
            delete states.top();
            states.pop();
        }
    }
    else
    {
        endApplication();
        window->close();
    }
}

//Render
void Game::render()
{

    sf::Texture tBackground;
    tBackground.loadFromFile("images/background.jpg");
    sf::Sprite sBackground(tBackground);

    window->clear();

    if (!states.empty())
        states.top()->render();

    window->draw(sBackground);
    window->display();
}

//Core
int Game::run()
{
    while (window->isOpen())
    {
        updateDelta();
        update();
        render();
    }
    return EXIT_SUCCESS;
}
