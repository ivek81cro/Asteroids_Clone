#include "stdafx.h"
#include "GameState.h"

//Constructors / Destructors
GameState::GameState(StateData* state_data)
        : State(state_data)
        , score_(0)
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

//Initializer functions
void GameState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
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
    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    p_menu_ = new PauseMenu(state_data_->gfx_settings_->resolution_, font_);

    p_menu_->AddButton("QUIT", window_->getSize().y - gui::PercToPixelY(13.89f, vm), gui::PercToPixelX(19.53f, vm),
                       gui::PercToPixelY(6.94f, vm), gui::CalcFontSIze(vm, 40), "Quit");
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
    for (int i = 0; i < 1; ++i)
        entities_.push_back(std::unique_ptr<Asteroid>(new Asteroid(static_cast<float>(rand() % (window_->getSize().x)),
                                                                   static_cast<float>(rand() % (window_->getSize().y)),
                                                                    1,
                                                                   textures_[ "ASTEROID" ])));
}

void GameState::FireBullet(Ship* s)
{
    entities_.push_back(std::unique_ptr<Bullet>(
        new Bullet(s->GetPosition().x, s->GetPosition().y, textures_[ "BULLET" ], s->GetAngle())));
}

void GameState::UpdateInput(const float& delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))) && GetKeytime())
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
    //Select ship from entites
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

    //Ship fires bullet if alive, if key cooldown time elapsed
    bullet_cooldown_ = bullet_clock_.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("FIRE"))) && bullet_cooldown_.asSeconds() > 0.25f &&
        s->IsAlive() && !s->IsExploding())
    {
        bullet_clock_.restart();
        FireBullet(s);
    }    
}

void GameState::UpdatePauseMenuButtons()
{
    if (p_menu_->IsButtonPressed("QUIT"))
        EndState();
}

void GameState::CheckEntitiesAlive(const float& delta)
{
    //Check if entity is alive, remove ones that are not
    entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
                                   [](const std::unique_ptr<Entity>& ent) { return !ent->IsAlive(); }),
                    entities_.end());
}

void GameState::CheckCollision()
{
    std::vector<std::unique_ptr<Entity>> new_entities;
    for (auto& it : entities_)
    {
        for (auto& it2 : entities_)
        {
            if (it->GetName() == "asteroid" && it2->GetName() == "bullet" && !it->IsExploding())
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        new_entities.push_back(std::unique_ptr<Asteroid>(new Asteroid(it->Getposition().x,
                                                                                      it->Getposition().y,
                                                                                      it->GetLevel() + 1,
                                                                                      textures_[ "ASTEROID" ])));
                    }
                    score_ += static_cast<Asteroid*>(it.get())->GetPoints();
                    it2->SetAlive(false);
                    it->SetAlive(false);
                }
            }
            if (it->GetName() == "ship" && it2->GetName() == "asteroid" && !it->IsExploding() &&
                !it2->IsExploding() && !static_cast<Ship*>(it.get())->ShieldsUp())
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    it->SetAlive(false);
                }
            }
        }
    }
    if (new_entities.size() != 0)
    {
        std::move(new_entities.begin(), new_entities.end(), std::back_inserter(entities_));
        new_entities.clear();
    }
}

void GameState::Update(const float& delta)
{
    //If all asteroids are destroyed
    if (entities_.size() < 2 && paused_== false && entities_[0].get()->GetName() == "ship")
    {
        states_->push(new ScoreState(state_data_, score_));
        paused_ = true;
    }

    UpdateMousePositions();
    UpdateKeytime(delta);
    UpdateInput(delta);

    if (!paused_)
    {
        UpdatePlayerInput(delta);
        CheckEntitiesAlive(delta);
        CheckCollision();
    }
    else
    {
        p_menu_->Update(mouse_pos_view_);
        UpdatePauseMenuButtons();
    }

    //Update entities
    for (auto& it : entities_)
    {
        if (it->GetName() == "bullet")
            static_cast<Bullet*>(it.get())->SetLifeTime(delta); //Decrease lifetime for elapsed time

        if ((it)->GetName() != "ship")
            it->Move(0, 0, delta); //Movement for asteroids and bullets

        it->Update(delta, window_->getSize()); //Update each entity
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
