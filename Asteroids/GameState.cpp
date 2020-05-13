#include "stdafx.h"
#include "GameState.h"

//Constructors / Destructors
GameState::GameState(StateData* state_data)
        : State(state_data)
        , score_(0)
        , player_lives_(3)
        , game_level_(1)
        , current_level_(1)
        , ufo_active_(false)
        , ufo_max_per_level_(rand() % 2 + 4)
{

    entity_scale_factor_ = state_data_->gfx_settings_->resolution_.width / 1280.f;
    enemy_time           = static_cast<float>(rand() % 10 + 20);

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
}

//Initializer functions
void GameState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
}

/**
    initialize keybinds 
*/
void GameState::InitKeybinds()
{
    std::ifstream ifs(*state_data_->path_game_state_keys_);
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

/**
    Load textures
*/
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
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    if (!textures_[ "ENEMYUFO" ].loadFromFile("Resources/Images/enemy_ufo.png"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_ENEMYUFO_TEXTURE";
    }

    if (!textures_[ "ENEMYBULLET" ].loadFromFile("Resources/Images/fire_blue.png"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_ENEMYBULLET_EXTURE";
    }

    if (!textures_[ "LIFE" ].loadFromFile("Resources/Images/life.png"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_ENEMYBULLET_EXTURE";
    }
}

/**
    Pause menu
*/
void GameState::InitPauseMenu()
{
    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    p_menu_ = std::unique_ptr<PauseMenu>(new PauseMenu(state_data_->gfx_settings_->resolution_, font_));

    p_menu_->AddButton("QUIT", window_->getSize().y - gui::PercToPixelY(13.89f, vm), gui::PercToPixelX(19.53f, vm),
                       gui::PercToPixelY(6.94f, vm), gui::CalcFontSize(vm, 40), "Quit");
}

/**
    initialize background
*/
void GameState::InitBackground()
{
    background_.setSize(
        sf::Vector2f(static_cast<float>(window_->getSize().x), static_cast<float>(window_->getSize().y)));

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
}

/**
    initialize player ship
*/
void GameState::InitPlayer()
{
    entities_.push_back(std::unique_ptr<Ship>(new Ship(static_cast<float>(window_->getSize().x / 2),
                                                       static_cast<float>(window_->getSize().y / 2),
                                                       textures_[ "PLAYER_SHIP" ], entity_scale_factor_)));
}

/**
    initialize enemy when time
*/
void GameState::InitEnemyUfo()
{
    sf::Vector2f ufo_position(static_cast<float>(rand() % window_->getSize().x), static_cast<float>(rand() % window_->getSize().y));

    entities_.push_back(std::unique_ptr<EnemyUfo>(
        new EnemyUfo(ufo_position.x, ufo_position.y, textures_[ "ENEMYUFO" ], entity_scale_factor_, current_level_)));

    ufo_active_ = true;
    --ufo_max_per_level_;
}

/**
    initialize asteroids
*/
void GameState::InitAsteroids()
{
    for (int i = 0; i <= 1 * current_level_; ++i)
        entities_.push_back(std::unique_ptr<Asteroid>(new Asteroid(static_cast<float>(rand() % (window_->getSize().x)),
                                                                   static_cast<float>(rand() % (window_->getSize().y)),
                                                                   1, textures_[ "ASTEROID" ], entity_scale_factor_, game_level_)));
}

/**
    initialize text objects in game state
*/
void GameState::InitTextItems()
{
    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    lives_text_.setFont(font_);
    lives_text_.setPosition(sf::Vector2f(gui::PercToPixelX(1.f, vm), gui::PercToPixelY(95.f, vm)));
    lives_text_.setCharacterSize(gui::CalcFontSize(vm, 85));
    lives_text_.setFillColor(sf::Color(255, 255, 255, 200));

    std::string lives_text = "Lives: ";

    lives_text_.setString(lives_text.append(std::to_string(player_lives_)));

    score_text_.setFont(font_);
    score_text_.setPosition(sf::Vector2f(gui::PercToPixelX(85.f, vm), gui::PercToPixelY(95.f, vm)));
    score_text_.setCharacterSize(gui::CalcFontSize(vm, 85));
    score_text_.setFillColor(sf::Color(255, 255, 255, 200));
    std::string score_text = "Current score: ";

    score_text_.setString(score_text.append(std::to_string(score_)));

    level_text_.setFont(font_);
    level_text_.setPosition(sf::Vector2f(gui::PercToPixelX(42.f, vm), gui::PercToPixelY(95.f, vm)));
    level_text_.setCharacterSize(gui::CalcFontSize(vm, 85));
    level_text_.setFillColor(sf::Color(255, 255, 255, 200));
    std::string level_text = "Current Level: ";

    level_text_.setString(level_text.append(std::to_string(current_level_)));

    invoulnerable_text_.setFont(font_);
    invoulnerable_text_.setPosition(sf::Vector2f(gui::PercToPixelX(42.f, vm), gui::PercToPixelY(90.f, vm)));
    invoulnerable_text_.setCharacterSize(gui::CalcFontSize(vm, 70));
    invoulnerable_text_.setFillColor(sf::Color(255, 0, 0, 200));
    invoulnerable_text_.setOutlineThickness(2);
    std::string invoulnerable_text = "=INVOULNERABLE=";

    invoulnerable_text_.setString(invoulnerable_text);
}

/**
    fire bullet from ship
*/
void GameState::FireBullet(Ship* s)
{
    entities_.push_back(std::unique_ptr<Bullet>(
        new Bullet(s->GetPosition().x, s->GetPosition().y, textures_[ "BULLET" ], s->GetAngle(), entity_scale_factor_, "bullet")));
}

/**
    If esc pressed enter into pause state
*/
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
/**
    Player input register function
*/
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
    //If ship not alive, reset player and remove life
    if (s == nullptr)
    {
        InitPlayer();

        --player_lives_;

        if (player_lives_ <= 0)
        {
            states_->push(std::unique_ptr<State>(new ScoreState(state_data_, score_,true)));
            paused_ = true;
            EndState();
        }
    }
    else
    {
        s->ResetAnimationName();//If not rotating return default animation
        InitTextItems();

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("FIRE"))) &&
            bullet_cooldown_.asSeconds() > 0.25f && s->IsAlive() && !s->IsExploding())
        {
            bullet_clock_.restart();
            FireBullet(s);
        }
    }
}

/**
    If pause is on and quit pressed
*/
void GameState::UpdatePauseMenuButtons()
{
    if (p_menu_->IsButtonPressed("QUIT"))
        EndState();
}

/**
    Check if entity is alive, remove ones that are not
*/
void GameState::CheckEntitiesAlive(const float& delta)
{
    entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
                                   [](const std::unique_ptr<Entity>& ent) { return !ent->IsAlive(); }),
                    entities_.end());
}

/**
    Check if entites are colliding
*/
void GameState::CheckCollision()
{

    std::vector<std::unique_ptr<Entity>> new_entities;
    for (auto& it : entities_)
    {
        for (auto& it2 : entities_)
        {
            //Check collision between ship bullets and asteroids
            if (it->GetName() == "asteroid" && it2->GetName() == "bullet" && !it->IsExploding())
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    //Split asteroid in 3 smaller ones
                    for (int i = 0; i < 3; ++i)
                    {
                        new_entities.push_back(std::unique_ptr<Asteroid>(
                            new Asteroid(it->GetPosition().x, it->GetPosition().y, it->GetLevel() + 1,
                                         textures_[ "ASTEROID" ], entity_scale_factor_, game_level_)));
                    }
                    score_ += static_cast<Asteroid*>(it.get())->GetPoints();
                    it2->SetAlive(false);
                    it->SetAlive(false);
                }
            }

            //Check collision between ship and asteroids or ship and enemy bullets
            if (it->GetName() == "ship" && (it2->GetName() == "asteroid" || it2->GetName() == "e_bullet") && !it->IsExploding() &&
                !it2->IsExploding() && it2->IsAlive() && !static_cast<Ship*>(it.get())->ShieldsUp())
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    it->SetAlive(false);
                }
            }

            //Collision between ship and drop
            if (it->GetName() == "ship" && (it2->GetName() == "life"))
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {                    
                    ++player_lives_;
                    it2->SetAlive(false);
                }
            }

            //Check collision between ship bullet and UFO, and ship and ufo in case of suicide run
            if (ufo_active_ && it->GetName() == "enemy_ufo" && !static_cast<EnemyUfo*>(it.get())->GetInvoulnerability() && 
                (it2->GetName() == "bullet" || it2->GetName() == "ship"))
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    it->SetAlive(false);
                    it2->SetAlive(false);

                    ufo_active_ = false;
                    score_ += static_cast<EnemyUfo*>(it.get())->GetPoints();

                    int ra = rand() % 50;
                    if (ra % 3 == 0)//Randomise if drop happens
                    {
                        entities_.push_back(
                            std::unique_ptr<DropLife>(new DropLife(it.get()->GetPosition().x, it.get()->GetPosition().y,
                                                                   textures_[ "LIFE" ], entity_scale_factor_)));
                    }
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

/**
    update all entities
*/
void GameState::UpdateEntities(const float& delta)
{
    //Update entities
    for (auto& it : entities_)
    {
        if (it->GetName() == "bullet" || it->GetName() == "e_bullet")
            static_cast<Bullet*>(it.get())->SetLifeTime(delta); //Decrease bullet lifetime for elapsed time

        if ((it)->GetName() != "ship")
            it->Move(0, 0, delta); //Movement for asteroids and bullets

        it->Update(delta, window_->getSize()); //Update each entity
    }
}

/**
    Update for enemy
*/
void GameState::UpdateEnemy(const float& delta)
{
    EnemyUfo* e = nullptr;
    
    //If enemy timer elapsed and there is no active enemy and limit of appearance not exceeded, create one
    if (enemy_time < 0 && !ufo_active_ && ufo_max_per_level_ > 0)
    {
        InitEnemyUfo();

        e          = static_cast<EnemyUfo*>(entities_[ entities_.size() - 1 ].get());
        enemy_time = static_cast<float>(rand() % 10 + 20);
    }

    if (ufo_active_)
    {
        for (auto& it : entities_)
        {
            if (it->GetName() == "enemy_ufo")
            {
                e = static_cast<EnemyUfo*>(it.get());
            }
        }
        if (e->IsAlive())
        {
            e->SetLifeTime(delta);//Time duration decrease enemy is active
            if (e != nullptr && e->GetFireCooldown() < 0)//Fire bullets every certain ammount of time
            {
                float angle = 360.f;
                while (angle > 0.f)
                {
                    entities_.push_back(std::unique_ptr<Bullet>(new Bullet(e->GetPosition().x, e->GetPosition().y,
                                                                           textures_[ "ENEMYBULLET" ], angle,
                                                                           entity_scale_factor_, "e_bullet")));

                    angle -= current_level_ > 1 ? 120.f / current_level_ : 120.f;//Set angle of shooting depending on level of game
                }
                e->ResetFireCooldown();
            }
        }
        else
            ufo_active_ = false;
    }
    //Prevent counting if max enemy count is exceeded
    else if (enemy_time > -1.f)
    {
        enemy_time -= delta;
    }
}

void GameState::Update(const float& delta)
{
    IfEnd();
    UpdateMousePositions();
    UpdateKeytime(delta);
    UpdateInput(delta);

    if (!paused_)
    {
        UpdatePlayerInput(delta);
        UpdateEnemy(delta);
        CheckCollision();
        CheckEntitiesAlive(delta);
        UpdateEntities(delta);
    }
    else
    {
        p_menu_->Update(mouse_pos_view_);
        UpdatePauseMenuButtons();
    }
}

/**
    Check if all asteroids and enemy is cleared, next level
*/
void GameState::IfEnd()
{
    //If all asteroids are destroyed
    if (entities_.size() < 2 && paused_ == false && entities_[ 0 ].get()->GetName() == "ship")
    {
        game_level_ += 0.3f;
        ++current_level_;

        ufo_max_per_level_ = rand() % 2 + 4;
        enemy_time         = static_cast<float>(rand() % 10 + 20);

        InitAsteroids();
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
        if (it.get()->GetName() == "ship" && static_cast<Ship*>(it.get())->ShieldsUp())
            target->draw(invoulnerable_text_);

        it->Render(*target);
    }

    target->draw(lives_text_);
    target->draw(score_text_);
    target->draw(level_text_);

    if (paused_)
    {
        p_menu_->Render(*target);
    }
}
