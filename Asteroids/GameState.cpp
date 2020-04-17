#include "GameState.h"

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitKeybinds();
    InitFonts();
    InitTextures();
    InitPauseMenu();
    InitBackground();
    InitPlayer();
    InitAsteroids();
}

GameState::~GameState()
{
    delete p_menu_;
}

void GameState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
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
    if (!textures_[ "PLAYER_SHIP" ].loadFromFile("Resources/Images/ship_inline.png"))
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

void GameState::InitPauseMenu()
{
    p_menu_ = new PauseMenu(*window_, font_);
}

void GameState::InitBackground()
{
    background_.setSize(
        sf::Vector2f(static_cast<float>(window_->getSize().x), static_cast<float>(window_->getSize().y)));

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
}

void GameState::InitPlayer()
{
    entities_.push_back(
        std::unique_ptr<Ship>(new Ship(static_cast<float>(window_->getSize().x / 2),
                                       static_cast<float>(window_->getSize().y / 2), textures_["PLAYER_SHIP"])));
}

void GameState::InitAsteroids()
{
    for (int i = 0; i < 10; ++i)
        entities_.push_back(std::unique_ptr<Asteroid>(new Asteroid(static_cast<float>(rand() % (window_->getSize().x)),
                                                                   static_cast<float>(rand() % (window_->getSize().y)),
                                                                   textures_[ "ASTEROID" ])));
}

void GameState::FireBullet(Ship* s)
{
    entities_.push_back(std::unique_ptr<Bullet>(
        new Bullet(s->GetPosition().x, s->GetPosition().y, textures_[ "BULLET" ], s->GetAngle())));
}

void GameState::UpdateInput(const float& delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
    {
        if (!paused_)
            PauseState();
        else
           UnpauseState();
    }
}

//Update functions
void GameState::UpdatePlayerInput(const float& delta)
{
    Ship* s = nullptr;
    for (auto& it : entities_)
    {
        if (it->GetName() == "ship")
        {
            s = static_cast<Ship*>(it.get());
        }
    }
    //If ship not alive, reset player
    if (s == nullptr)
    {
        InitPlayer();
        s = static_cast<Ship*>(entities_[ entities_.size() - 1 ].get());
    }

    s->ResetAnimationName();
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_UP"))))
        s->Move(0.f, -1.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_DOWN"))))
        s->Move(0.f, 1.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_LEFT"))))
        s->Move(-1.f, 0.f, delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_RIGHT"))))
        s->Move(1.f, 0.f, delta);

    //Bullet fire
    float time       = elapsed_coldown_.restart().asSeconds();
    bullet_cooldown_ = bullet_clock_.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("FIRE"))) && bullet_cooldown_.asSeconds() > 0.25f &&
        s->IsAlive())
    {
        bullet_clock_.restart();
        FireBullet(s);
    }    
}

void GameState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    if (!paused_)
    {
        UpdatePlayerInput(delta);

        //Check if entity is alive
        entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
                                       [](const std::unique_ptr<Entity>& ent) { return !ent->IsAlive(); }),
                        entities_.end());

        for (auto& it : entities_)
        {
            if (it->GetName() == "bullet")
                static_cast<Bullet*>(it.get())->SetLifeTime(delta);
            if ((it)->GetName() != "ship")
                it->Move(0, 0, delta);
            it->Update(delta, window_->getSize());
        }
    }
    else
    {
        p_menu_->Update();
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

    for (auto& it : entities_)
    {
        it->Render(*target);
    }

    if (paused_)
    {
        p_menu_->Render(*target);
    }
}
