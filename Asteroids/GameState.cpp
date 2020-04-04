#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
        : State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{

}

void GameState::updateKeybinds(const float& delta)
{
    checkForQuit();
}

void GameState::update(const float& delta)
{
    updateKeybinds(delta);
}

void GameState::render(sf::RenderTarget* target)
{
}
