#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
    state_data_     = state_data;
    window_         = state_data->window_;
    quit_           = false;
    states_         = state_data->states_;
    supported_keys_ = state_data->supported_keys_;
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
const float State::PercToPixelX(const float perc) const
{
    /*
    * Converts a percetage value to pixels relative to screen resolution in the x-axis.
    *
    * @param    float perc  The percentage value
    *
    * @return    float The calculated pixel value
    *
    */
    return std::floor(static_cast<float>(state_data_->gfx_settings_->resolution_.width) * (perc / 100.f));
}

const float State::PercToPixelY(const float perc) const
{
    /*
    * Converts a percetage value to pixels relative to screen resolution in the y-axis.
    *
    * @param    float perc  The percentage value
    *
    * @return    float The calculated pixel value
    *
    */
    return std::floor(static_cast<float>(state_data_->gfx_settings_->resolution_.height) * (perc / 100.f));
}

const unsigned State::CalcFontSIze() const
{
    return static_cast<unsigned>(
        (state_data_->gfx_settings_->resolution_.width + state_data_->gfx_settings_->resolution_.height) / 40);
}

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
