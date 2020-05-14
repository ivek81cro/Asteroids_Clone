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

SupportedKeys State::SelectEnumSupportedKeys(std::string key)
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

Keybinds State::SelectEnumKeybinds(std::string key)
{
    if (key == "CLOSE")
        return Keybinds::Close;
    else if (key == "FIRE")
        return Keybinds::Fire;
    else if (key == "MOVE_UP")
        return Keybinds::Move_up;
    else if (key == "MOVE_DOWN")
        return Keybinds::Move_down;
    else if (key == "MOVE_LEFT")
        return Keybinds::Move_left;
    else if (key == "MOVE_RIGHT")
        return Keybinds::Move_right;
    else
        return Keybinds::Unknown;
}