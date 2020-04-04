#include "Game.h"
#include "Constants.h"
#include "Level.h"

//Initialization
void Game::InitWindow()
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

    window_ = new sf::RenderWindow(windowBounds, title);
    window_->setKeyRepeatEnabled(false);
    window_->setFramerateLimit(frameRateLimit);
    window_->setVerticalSyncEnabled(vSyncEnabled);
}

void Game::InitStates()
{
    states_.push(new GameState(window_));
}

//Constructors/Destructors
Game::Game()
{
    InitWindow();
    InitStates();
}

Game::~Game()
{
    delete window_;

    while (!states_.empty())
    {
        delete states_.top();
        states_.pop();
    }
}

//Regular
void Game::EndApplication()
{

}

//Update
void Game::UpdateDelta()
{
    delta_ = clock_.restart().asSeconds();
}

void Game::UpdateSFMLEvents()
{
    while (window_->pollEvent(event_))
    {
        if (event_.type == sf::Event::Closed)
            window_->close();
    }
}

void Game::Update()
{
    UpdateSFMLEvents();

    if (!states_.empty())
    {
        states_.top()->Update(delta_);

        if (states_.top()->GetQuit())
        {
            states_.top()->EndState();
            delete states_.top();
            states_.pop();
        }
    }
    else
    {
        EndApplication();
        window_->close();
    }
}

//Render
void Game::Render()
{

    sf::Texture tBackground;
    tBackground.loadFromFile("images/background.jpg");
    sf::Sprite sBackground(tBackground);

    window_->clear();

    if (!states_.empty())
        states_.top()->Render();

    window_->draw(sBackground);
    window_->display();
}

//Core
int Game::Run()
{
    while (window_->isOpen())
    {
        UpdateDelta();
        Update();
        Render();
    }
    return EXIT_SUCCESS;
}
