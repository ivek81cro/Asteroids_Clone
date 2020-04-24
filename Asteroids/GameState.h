#ifndef GAMESTATE_H_
#define GAMESTATE_H_

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
    void Update(const float& delta);

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

    //Initializer Functions
    void InitKeybinds();
    void InitFonts();
    void InitTextures();
    void InitPauseMenu();
    void InitBackground();
    void InitPlayer();
    void InitAsteroids();
    void FireBullet(Ship* s);
};

#endif // !GAMESTATE_H_
