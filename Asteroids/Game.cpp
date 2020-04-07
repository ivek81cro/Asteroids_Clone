#include "Game.h"

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

void Game::InitKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");
    if (ifs.is_open())
    {
        std::string key       = "";
        int         key_value = 0;
        while (ifs >> key >> key_value)
        {
            supported_keys_[ key ] = key_value;
        }
    }
    ifs.close();
}

void Game::InitStates()
{
    states_.push(new MainMenuState(window_, &supported_keys_, &states_));
}

//Constructors/Destructors
Game::Game()
{
    InitWindow();
    InitKeys();
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
    window_->clear();

    if (!states_.empty())
        states_.top()->Render();

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
