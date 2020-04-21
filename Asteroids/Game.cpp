#include "stdafx.h"
#include "Game.h"

void Game::InitVariables()
{
    window_     = nullptr;
    delta_      = 0.f;
}

void Game::InitGraphicsSettings()
{
    gfx_settings_.LoadFromFile("Config/graphics.ini");
}

//Initialization functions
void Game::InitWindow()
{
    if (gfx_settings_.fullscreen_)
    {
        window_ = new sf::RenderWindow(gfx_settings_.resolution_, gfx_settings_.title_, sf::Style::Fullscreen,
                                       gfx_settings_.context_settings_);
    }
    else
    {
        window_ = new sf::RenderWindow(gfx_settings_.resolution_, gfx_settings_.title_,
                                       sf::Style::Titlebar | sf::Style::Close, gfx_settings_.context_settings_);
    }

    window_->setFramerateLimit(gfx_settings_.frame_rate_limit_);
    window_->setVerticalSyncEnabled(gfx_settings_.v_sync_);
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
    InitVariables();
    InitGraphicsSettings();
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

//Update functions
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

//Render functions
void Game::Render()
{
    window_->clear();

    if (!states_.empty())
        states_.top()->Render();

    window_->display();
}

//Core function
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
