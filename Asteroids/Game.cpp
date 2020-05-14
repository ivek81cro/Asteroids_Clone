#include "stdafx.h"
#include "Game.h"

//Constructors/Destructors
Game::Game()
{
    InitVariables();
    InitGraphicsSettings();
    InitWindow();
    InitKeys();
    InitStateData();
    InitStates();
}

Game::~Game()
{

    while (!states_.empty())
    {
        states_.pop();
    }
}

//Initialization functions
void Game::InitVariables()
{
    window_ = nullptr;
    delta_  = 0.f;
}


void Game::InitGraphicsSettings()
{
    gfx_settings_.LoadFromFile(PATH_FILE_GRAPHICS);
}

/**
    Initializes data in State.cpp class StateData
*/
void Game::InitStateData()
{
    state_data_.window_               = window_.get();
    state_data_.gfx_settings_         = &gfx_settings_;
    state_data_.supported_keys_       = &supported_keys_;
    state_data_.states_               = &states_;
    state_data_.event_                = &event_;
    state_data_.path_game_state_keys_ = &gfx_settings_.path_game_state_keys_;
}

/**
    Initialize window
*/
void Game::InitWindow()
{
    if (gfx_settings_.fullscreen_)
    {
        window_ = std::unique_ptr<sf::RenderWindow>(
            new sf::RenderWindow(gfx_settings_.resolution_, gfx_settings_.title_, 
                                 sf::Style::Fullscreen, gfx_settings_.context_settings_));
    }
    else
    {
        window_ = std::unique_ptr<sf::RenderWindow>(
            new sf::RenderWindow(gfx_settings_.resolution_, gfx_settings_.title_,
                                 sf::Style::Titlebar | sf::Style::Close, gfx_settings_.context_settings_));
    }

    window_->setFramerateLimit(gfx_settings_.frame_rate_limit_);
    window_->setVerticalSyncEnabled(gfx_settings_.v_sync_);
}

/**
    Initialize supported keys, keybinds
*/
void Game::InitKeys()
{
    std::ifstream ifs(PATH_FILE_SUPPORTED_KEYS);
    if (ifs.is_open())
    {
        std::string key       = "";
        int         key_value = 0;
        while (ifs >> key >> key_value)
        {
            SupportedKeys key_e = SelectEnum(key);

            if (key_e != SupportedKeys::Unsupported)
                supported_keys_[ key_e ] = key_value;
        }
    }
    ifs.close();
}

/**
    Push initialized state on stack states_
*/
void Game::InitStates()
{
    states_.push(std::unique_ptr<State>(new MainMenuState(&state_data_)));
}

SupportedKeys Game::SelectEnum(std::string key)
{
    if (key == "Up")
        return SupportedKeys::Up;
    else if (key == "Down")
        return SupportedKeys::Down;
    else if (key == "Left")
        return SupportedKeys::Left;
    else if (key == "Right")
        return SupportedKeys::Right;
    else if (key == "Escape")
        return SupportedKeys::Escape;
    else if (key == "Space")
        return SupportedKeys::Space;
    else if (key == "W")
        return SupportedKeys::W;
    else if (key == "A")
        return SupportedKeys::A;
    else if (key == "S")
        return SupportedKeys::S;
    else if (key == "D")
        return SupportedKeys::D;
    else
        return SupportedKeys::Unsupported;
}

//Regular
void Game::EndApplication()
{
}

/**
    Time management
*/
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
        if (window_->hasFocus())
        {
            states_.top()->Update(delta_);

            if (states_.top()->GetQuit())
            {
                states_.top()->EndState();
                states_.pop();
            }
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
void Game::Run()
{
    while (window_->isOpen())
    {
        UpdateDelta();
        Update();
        Render();
    }
}
