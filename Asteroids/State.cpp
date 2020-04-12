#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
{
    window_         = window;
    quit_           = false;
    states_         = states;
    supported_keys_ = supported_keys;
}

State::~State()
{
}

const bool& State::GetQuit() const
{
    return quit_;
}

void State::EndState()
{
    quit_ = true;
}

void State::UpdateMousePositions()
{
    mouse_pos_screen_ = sf::Mouse::getPosition();
    mouse_pos_window_ = sf::Mouse::getPosition(*window_);
    mouse_pos_view_   = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
}
