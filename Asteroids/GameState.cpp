#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
        : State(window)
{
}

GameState::~GameState()
{
}

void GameState::EndState()
{

}

void GameState::UpdateKeybinds(const float& delta)
{
    CheckForQuit();
}

void GameState::Update(const float& delta)
{
    UpdateKeybinds(delta);
}

void GameState::Render(sf::RenderTarget* target)
{
}
