#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
{
    window_         = window;
    quit_           = false;
    states_         = states;
    supported_keys_ = supported_keys;
    paused_         = false;
    keytime_        = 0.f;
    keytime_max_    = 10.f;
}

State::~State()
{
}

//Accessor
const bool& State::GetQuit() const
{
    return quit_;
}

const bool State::GetKeytime()
{
    if (keytime_ >= keytime_max_)
    {
        keytime_ = 0.f;
        return true;
    }
    return false;
}

//Functions
void State::EndState()
{
    quit_ = true;
}

void State::PauseState()
{
    paused_ = true;
}

void State::UnpauseState()
{
    paused_ = false;
}

void State::UpdateMousePositions()
{
    mouse_pos_screen_ = sf::Mouse::getPosition();
    mouse_pos_window_ = sf::Mouse::getPosition(*window_);
    mouse_pos_view_   = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
}

void State::UpdateKeytime(const float& delta)
{
    if (keytime_ < keytime_max_)
        keytime_ += 100.f * delta;
}
