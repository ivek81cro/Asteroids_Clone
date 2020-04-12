#include "GameState.h"

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitKeybinds();
    InitTextures();
    InitBackground();
    InitPlayer();
    InitAsteroids();
}

GameState::~GameState()
{
    delete ship_;
    while (!asteroid_.empty())
        asteroid_.pop_back();
    while (!bullet_.empty())
        bullet_.pop_back();
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

    if (!textures_[ "ASTEROID" ].loadFromFile("Resources/Images/rock.png"))
    {
        throw "ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_ASTEROID_TEXTURE";
    }

    if (!textures_[ "BULLET" ].loadFromFile("Resources/Images/fire_red_reverse.png"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BULLET_EXTURE";
    }

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACLGROUND_TEXTURE";
    }
}

void GameState::InitBackground()
{
    background_.setSize(
        sf::Vector2f(static_cast<float>(window_->getSize().x), static_cast<float>(window_->getSize().y)));

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
}

void GameState::InitPlayer()
{
    ship_ = new Ship(static_cast<float>(window_->getSize().x / 2), static_cast<float>(window_->getSize().y / 2),
                     textures_[ "PLAYER_SHIP" ]);
}

void GameState::InitAsteroids()
{
    for (int i = 0; i < 10; ++i)
        asteroid_.push_back(new Asteroid(static_cast<float>(rand() % (window_->getSize().x)),
                                         static_cast<float>(rand() % (window_->getSize().y)),
                                         textures_[ "ASTEROID" ]));
}

void GameState::FireBullet()
{
    bullet_.push_back(
        new Bullet(ship_->GetPosition().x, ship_->GetPosition().y, textures_[ "BULLET" ], ship_->GetAngle()));
}

//Update functions
void GameState::UpdateInput(const float& delta)
{
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_UP"))))
        ship_->Move(0.f, -1.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_DOWN"))))
        ship_->Move(0.f, 1.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_LEFT"))))
        ship_->Move(-1.f, 0.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_RIGHT"))))
        ship_->Move(1.f, 0.f, delta);

    //Bullet fire
    float time       = elapsed_coldown_.restart().asSeconds();
    bullet_cooldown_ = bullet_clock_.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("FIRE"))) && bullet_cooldown_.asSeconds() > 0.25f)
    {
        bullet_clock_.restart();
        FireBullet();
    }

    //Close with esc button
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
        EndState();
}

void GameState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    //Check if bullet is alive
    bullet_.erase(std::remove_if(bullet_.begin(), bullet_.end(), [](Bullet* bullet) { return !(*bullet).IsAlive(); }),
                  bullet_.end());

    //Check if asteroid is alive
    asteroid_.erase(
        std::remove_if(asteroid_.begin(), asteroid_.end(), [](Asteroid* asteroid) { return !(*asteroid).IsAlive(); }),
        asteroid_.end());

    ship_->Update(delta, window_->getSize());

    for (std::vector<Asteroid*>::iterator it = asteroid_.begin(); it != asteroid_.end(); ++it)
    {
        (*it)->Move(0, 0, delta);
        (*it)->Update(delta, window_->getSize());
    }

    for (std::vector<Bullet*>::iterator it = bullet_.begin(); it != bullet_.end(); ++it)
    {
        (*it)->SetLifeTime(delta);
        (*it)->Move(0, 0, delta);
        (*it)->Update(delta, window_->getSize());
    }
}

//Render Functions
void GameState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }

    target->draw(background_);

    ship_->Render(target);

    for (std::vector<Asteroid*>::iterator it = asteroid_.begin(); it != asteroid_.end(); ++it)
    {
        (*it)->Render(target);
    }

    for (std::vector<Bullet*>::iterator it = bullet_.begin(); it != bullet_.end(); ++it)
    {
        (*it)->Render(target);
    }
}
