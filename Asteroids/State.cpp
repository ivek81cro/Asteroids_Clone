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

void State::LogMessage(std::string& message)
{

}

SupportedKey_e State::SelectEnumSupportedKeys(std::string key)
{
    if (key == "Up")
        return SupportedKey_e::Up;
    else if (key == "Down")
        return SupportedKey_e::Down;
    else if (key == "Left")
        return SupportedKey_e::Left;
    else if (key == "Right")
        return SupportedKey_e::Right;
    else if (key == "Escape")
        return SupportedKey_e::Escape;
    else if (key == "Space")
        return SupportedKey_e::Space;
    else if (key == "W")
        return SupportedKey_e::W;
    else if (key == "A")
        return SupportedKey_e::A;
    else if (key == "S")
        return SupportedKey_e::S;
    else if (key == "D")
        return SupportedKey_e::D;
    else
        return SupportedKey_e::Unsupported;
}

Keybind_e State::SelectEnumKeybinds(std::string key)
{
    if (key == "CLOSE")
        return Keybind_e::Close;
    else if (key == "FIRE")
        return Keybind_e::Fire;
    else if (key == "MOVE_UP")
        return Keybind_e::Move_up;
    else if (key == "MOVE_DOWN")
        return Keybind_e::Move_down;
    else if (key == "MOVE_LEFT")
        return Keybind_e::Move_left;
    else if (key == "MOVE_RIGHT")
        return Keybind_e::Move_right;
    else
        return Keybind_e::Unknown;
}