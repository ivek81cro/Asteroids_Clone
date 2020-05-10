#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "ScoreState.h"
#include "PauseMenu.h"
#include "State.h"

class GameState : public State
{
  public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Update functions
    void UpdateInput(const float& delta);
    void UpdatePlayerInput(const float& delta);
    void UpdatePauseMenuButtons();
    void CheckEntitiesAlive(const float& delta);
    void CheckCollision();
    void UpdateEntities(const float& delta);
    void UpdateEnemy(const float& delta);
    void Update(const float& delta);
    void IfEnd();

    //Render functions
    void Render(sf::RenderTarget* target = nullptr);

  private:
    PauseMenu* p_menu_;

    std::vector<std::unique_ptr<Entity>> entities_;

    sf::RectangleShape background_;
    sf::Font           font_;
    sf::Clock          bullet_clock_;
    sf::Time           bullet_cooldown_;
    sf::Text           lives_text_;
    sf::Text           score_text_;
    sf::Text           invoulnerable_text_;
    sf::Text           level_text_;

    int   ufo_max_per_level_;
    int   score_;
    int   times_killed_;
    int   current_level_;
    bool  ufo_active_;
    float entity_scale_factor_;
    float game_level_;
    float enemy_time;

    //Initializer Functions
    void InitKeybinds();
    void InitFonts();
    void InitTextures();
    void InitPauseMenu();
    void InitBackground();
    void InitPlayer();
    void InitEnemyUfo();
    void InitAsteroids();
    void InitTextItems(Ship* s);
    void FireBullet(Ship* s);
};

#endif // !GAMESTATE_H_
