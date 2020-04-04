#include "Game.h"
#include "Constants.h"
#include "Level.h"

//Initialization
void Game::InitWindow()
{
    std::ifstream ifs("Config/window.ini");
    sf::VideoMode window_bounds(800, 600);
    std::string   title;
    unsigned      frame_rate_limit = 120;
    bool          v_sync_enabled   = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> frame_rate_limit;
        ifs >> v_sync_enabled;
    }

    ifs.close();

    window_ = new sf::RenderWindow(window_bounds, title);
    window_->setKeyRepeatEnabled(false);
    window_->setFramerateLimit(frame_rate_limit);
    window_->setVerticalSyncEnabled(v_sync_enabled);
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
