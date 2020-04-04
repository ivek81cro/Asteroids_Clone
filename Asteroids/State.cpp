#include "State.h"

State::State(sf::RenderWindow* window)
{
    this->window_ = window;
    quit_     = false;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        quit_ = true;
    }
}
