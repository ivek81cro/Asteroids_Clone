#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitKeybinds();
}

GameState::~GameState()
{
}

void GameState::EndState()
{
}

void GameState::InitKeybinds()
{
    std::ifstream ifs("Config/gamestate_keybinds.ini");
    if (ifs.is_open())
    {
        std::string key  = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            keybinds_[ key ] = supported_keys_->at(key2);
        }
    }
    ifs.close();
}

void GameState::UpdateInput(const float& delta)
{
    CheckForQuit();

    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_UP"))))
        player_.Move(delta, 0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_DOWN"))))
        player_.Move(delta, 0.f, 1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_LEFT"))))
        player_.Move(delta, -1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_RIGHT"))))
        player_.Move(delta, 1.f, 0.f);
}

void GameState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);
    player_.Update(delta);
}

void GameState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }
    player_.Render(target);
}
