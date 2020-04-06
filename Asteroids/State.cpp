#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys)
{
    this->window_   = window;
    quit_           = false;
    supported_keys_ = supported_keys;
}

State::~State()
{
}

const bool& State::GetQuit() const
{
    return quit_;
}

void State::CheckForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
    {
        quit_ = true;
    }
}

void State::UpdateMousePositions()
{
    mouse_pos_screen_ = sf::Mouse::getPosition();
    mouse_pos_window_ = sf::Mouse::getPosition(*window_);
    mouse_pos_view_   = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
}
