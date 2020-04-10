#include "GameState.h"

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitKeybinds();
    InitTextures();
    InitPlayer();
}

GameState::~GameState()
{
    delete player_;
}

//Initializer functions
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

void GameState::InitTextures()
{
    if (!textures_[ "PLAYER_SHIP" ].loadFromFile("Resources/Images/spaceship.png"))
    {
        throw "ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_SHIP_TEXTURE";
    }
}

void GameState::InitPlayer()
{
    player_ = new Ship(window_->getSize().x / 2, window_->getSize().y / 2, textures_[ "PLAYER_SHIP" ]);
}

//Update functions
void GameState::UpdateInput(const float& delta)
{
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_UP"))))
        player_->Move(0.f, -1.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_DOWN"))))
        player_->Move(0.f, 1.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_LEFT"))))
        player_->Move(-1.f, 0.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_RIGHT"))))
        player_->Move(1.f, 0.f, delta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
        EndState();
}

void GameState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);
    player_->Update(delta, window_->getSize());
}

//Render Functions
void GameState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }
    player_->Render(target);
}
