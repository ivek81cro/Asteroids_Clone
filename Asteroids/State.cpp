#include "stdafx.h"
#include "State.h"

/**
    Base class for states
*/
State::State(StateData* state_data)
{
    state_data_     = state_data;
    window_         = state_data->window_;
    quit_           = false;
    states_         = state_data->states_;
    supported_keys_ = state_data->supported_keys_;
    paused_         = false;
    keytime_        = 0.f;
    keytime_max_    = 20.f;
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

/**
    Updating mouse positions
*/
void State::UpdateMousePositions()
{
    mouse_pos_screen_ = sf::Mouse::getPosition();
    mouse_pos_window_ = sf::Mouse::getPosition(*window_);
    mouse_pos_view_   = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
}

/**
    Prevent fast key repeat
*/
void State::UpdateKeytime(const float& delta)
{
    if (keytime_ < keytime_max_)
        keytime_ += 100.f * delta;
}