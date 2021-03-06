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
    try
    {
        if (!font_.loadFromFile(PATH_FILE_FONTS))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_FONT_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FONT_FILE);
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
            Keybind_e key_e     = SelectEnumKeybinds(key);
            SupportedKey_e key2_e = SelectEnumSupportedKeys(key2);

            if (key_e != Keybind_e::Unknown && key2_e != SupportedKey_e::Unsupported)
                keybinds_[ key_e ] = supported_keys_->at(key2_e);
        }
    }
    ifs.close();
}

/**
    Load textures
*/
void GameState::InitTextures()
{
    try
    {
        if (!textures_[ Texture_e::Player_ship ].loadFromFile(PATH_TEXTURE_SHIP))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_SHIP_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
    try
    {
        if (!textures_[ Texture_e::Asteroid ].loadFromFile(PATH_TEXTURE_ASTEROID))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_ASTEROID_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
    try
    {
        if (!textures_[ Texture_e::Bullet ].loadFromFile(PATH_TEXTURE_BULLET_SHIP))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_BULLET_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
    try
    {
        if (!textures_[ Texture_e::Background_texture ].loadFromFile(PATH_TEXTURE_BACKGROUND_GAME))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_BACKGROUND_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
    try
    {
        if (!textures_[ Texture_e::Enemy_ufo ].loadFromFile(PATH_TEXTURE_ENEMY_UFO))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_ENEMY_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
    try
    {
        if (!textures_[ Texture_e::Bullet_enemy ].loadFromFile(PATH_TEXTURE_BULLET_ENEMY))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_BULLET_ENEMY_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
    try
    {
        if (!textures_[ Texture_e::Life ].loadFromFile(PATH_TEXTURE_LIFE))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_LIFE_TEXTURE_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FILE);
        EndState();
    }
}

/**
    Pause menu
*/
void GameState::InitPauseMenu()
{
    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    p_menu_ = std::unique_ptr<PauseMenu>(new PauseMenu(state_data_->gfx_settings_->resolution_, font_, *state_data_->btn_settings_));

    p_menu_->AddButton(Buttons::Quit, window_->getSize().y - gui::PercToPixelY(13.89f, vm), gui::PercToPixelX(19.53f, vm),
                       gui::PercToPixelY(6.94f, vm), gui::CalcFontSize(vm, 40), "Quit");
}

/**
    initialize background
*/
void GameState::InitBackground()
{
    background_.setSize(
        sf::Vector2f(static_cast<float>(window_->getSize().x), static_cast<float>(window_->getSize().y)));

    background_.setTexture(&textures_[ Texture_e::Background_texture ]);
}

/**
    initialize player ship
*/
void GameState::InitPlayer()
{
    entities_.push_back(std::unique_ptr<Ship>(new Ship(static_cast<float>(window_->getSize().x / 2),
                                                       static_cast<float>(window_->getSize().y / 2),
                                                       textures_[ Texture_e::Player_ship ], entity_scale_factor_)));
}

/**
    initialize enemy when time
*/
void GameState::InitEnemyUfo()
{
    sf::Vector2f ufo_position(static_cast<float>(rand() % window_->getSize().x), static_cast<float>(rand() % window_->getSize().y));

    entities_.push_back(std::unique_ptr<EnemyUfo>(
        new EnemyUfo(ufo_position.x, ufo_position.y, textures_[ Texture_e::Enemy_ufo ], entity_scale_factor_, current_level_)));

    ufo_active_ = true;
    --ufo_max_per_level_;
    enemy_bullet_clock_.restart();
}

/**
    initialize asteroids
*/
void GameState::InitAsteroids()
{
    for (int i = 0; i <= 1 * current_level_; ++i)
        entities_.push_back(std::unique_ptr<Asteroid>(new Asteroid(static_cast<float>(rand() % (window_->getSize().x)),
                                                                   static_cast<float>(rand() % (window_->getSize().y)),
                                                                   1, textures_[ Texture_e::Asteroid ], entity_scale_factor_, game_level_)));
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
    invoulnerable_text_.setFillColor(state_data_->btn_settings_->btn_txt_idle_);
    invoulnerable_text_.setOutlineThickness(2);
    std::string invoulnerable_text = "=INVULNERABLE=";

    invoulnerable_text_.setString(invoulnerable_text);
}

/**
    fire bullet from ship
*/
void GameState::FireBullet(Entity* s)
{
    entities_.push_back(std::unique_ptr<Bullet>(
        new Bullet(s->GetPosition().x, s->GetPosition().y, textures_[ Texture_e::Bullet ], s->GetAngle(), entity_scale_factor_, EntityName_e::Bullet)));
}

/**
    If esc pressed enter into pause state
*/
void GameState::UpdateInput(const float& delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at(Keybind_e::Close))) && GetKeytime())
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
    Entity* s = nullptr;
    for (auto& it : entities_)
    {
        if (it->GetName() == EntityName_e::Ship)
        {
            s = it.get();
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at(Keybind_e::Move_up))))
            s->Move(0.f, -1.f, delta);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at(Keybind_e::Move_down))))
            s->Move(0.f, 1.f, delta);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at(Keybind_e::Move_left))))
            s->Move(-1.f, 0.f, delta);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at(Keybind_e::Move_right))))
            s->Move(1.f, 0.f, delta);

        //Ship fires bullet if alive, if key cooldown time elapsed
        bullet_cooldown_ = bullet_clock_.getElapsedTime();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at(Keybind_e::Fire))) &&
            bullet_cooldown_.asSeconds() > 0.25f && s->GetAlive() && !s->IsExploding())
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
    if (p_menu_->IsButtonPressed(Buttons::Quit))
        EndState();
}

/**
    Check if entity is alive, remove ones that are not
*/
void GameState::CheckEntitiesAlive(const float& delta)
{
    entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
                                   [](const std::unique_ptr<Entity>& ent) { return !ent->GetAlive(); }),
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
            if (it->GetName() == EntityName_e::Asteroid && it2->GetName() == EntityName_e::Bullet && !it->IsExploding())
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    //Split asteroid in 3 smaller ones
                    for (int i = 0; i < 3; ++i)
                    {
                        new_entities.push_back(std::unique_ptr<Asteroid>(
                            new Asteroid(it->GetPosition().x, it->GetPosition().y, it->GetLevel() + 1,
                                         textures_[ Texture_e::Asteroid ], entity_scale_factor_, game_level_)));
                    }
                    score_ += it.get()->GetPoints();
                    it2->SetAlive(false);
                    it->SetAlive(false);
                }
            }

            //Check collision between ship and asteroids or ship and enemy bullets
            if (it->GetName() == EntityName_e::Ship && (it2->GetName() == EntityName_e::Asteroid || 
                it2->GetName() == EntityName_e::Bullet_enemy) && !it->IsExploding() && !it2->IsExploding() && 
                it2->GetAlive() && !it.get()->ShieldsUp())
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    it->SetAlive(false);
                }
            }

            //Collision between ship and drop
            if (it->GetName() == EntityName_e::Ship && (it2->GetName() == EntityName_e::Life))
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {                    
                    ++player_lives_;
                    it2->SetAlive(false);
                }
            }

            //Check collision between ship bullet and UFO, and ship and ufo in case of suicide run
            if (ufo_active_ && it->GetName() == EntityName_e::Enemy_ufo && !it.get()->ShieldsUp() && 
                (it2->GetName() == EntityName_e::Bullet || it2->GetName() == EntityName_e::Ship))
            {
                if (it->CheckCollision(it2->GetHitbox()))
                {
                    it->SetAlive(false);
                    it2->SetAlive(false);

                    ufo_active_ = false;
                    score_ += it.get()->GetPoints();

                    int ra = rand() % 50;
                    if (ra % 3 == 0)//Randomise if drop happens
                    {
                        entities_.push_back(
                            std::unique_ptr<DropLife>(new DropLife(it.get()->GetPosition().x, it.get()->GetPosition().y,
                                                                   textures_[ Texture_e::Life ], entity_scale_factor_)));
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
        if ((it)->GetName() != EntityName_e::Ship)
            it->Move(0, 0, delta); //Movement for asteroids and bullets

        it->Update(delta, window_->getSize()); //Update each entity
    }
}

/**
    Update for enemy
*/
void GameState::UpdateEnemy(const float& delta)
{
    Entity* e = nullptr;
    
    //If enemy timer elapsed and there is no active enemy and limit of appearance not exceeded, create one
    if (enemy_time < 0 && !ufo_active_ && ufo_max_per_level_ > 0)
    {
        InitEnemyUfo();

        e          = entities_[ entities_.size() - 1 ].get();
        enemy_time = static_cast<float>(rand() % 10 + 20);
    }

    if (ufo_active_)
    {
        for (auto& it : entities_)
        {
            if (it->GetName() == EntityName_e::Enemy_ufo)
            {
                e = it.get();
            }
        }
        if (e->GetAlive())
        {
            enemy_bullet_cooldown_ = enemy_bullet_clock_.getElapsedTime();
            if (e != nullptr && enemy_bullet_cooldown_.asSeconds() > 1.f)//Fire bullets every certain ammount of time
            {
                float angle = 360.f;
                while (angle > 0.f)
                {
                    entities_.push_back(std::unique_ptr<Bullet>(new Bullet(e->GetPosition().x, e->GetPosition().y,
                                                                           textures_[ Texture_e::Bullet_enemy ], angle,
                                                                           entity_scale_factor_, EntityName_e::Bullet_enemy)));

                    angle -= current_level_ > 1 ? 120.f / current_level_ : 120.f;//Set angle of shooting depending on level of game
                }
                enemy_bullet_clock_.restart();
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
    if (entities_.size() < 2 && paused_ == false && entities_[ 0 ].get()->GetName() == EntityName_e::Ship)
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
        if (it.get()->GetName() == EntityName_e::Ship && it.get()->ShieldsUp())
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
