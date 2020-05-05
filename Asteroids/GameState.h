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
    void Update(const float& delta);
    void IfEnd();

    //Render functions
    void Render(sf::RenderTarget* target = nullptr);

  private:
    sf::Font   font_;
    PauseMenu* p_menu_;

    std::vector<std::unique_ptr<Entity>> entities_;
    sf::RectangleShape                   background_;

    sf::Clock elapsed_coldown_;
    sf::Clock bullet_clock_;
    sf::Time  bullet_cooldown_;

    sf::Text lives_text_;
    sf::Text score_text_;
    sf::Text invoulnerable_text_;

    int   score_;
    int   times_killed_;
    float entity_scale_factor_;
    float game_level_;

    //Initializer Functions
    void InitKeybinds();
    void InitFonts();
    void InitTextures();
    void InitPauseMenu();
    void InitBackground();
    void InitPlayer();
    void InitAsteroids();
    void InitLivesText(Ship* s);
    void FireBullet(Ship* s);
};

#endif // !GAMESTATE_H_
