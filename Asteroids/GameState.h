#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"

class GameState : public State
{
  public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
    virtual ~GameState();

    //Update functions
    void UpdateInput(const float& delta);
    void Update(const float& delta);

    //Render functions
    void Render(sf::RenderTarget* target = nullptr);

  private:
    std::vector<std::unique_ptr<Entity>>  entities_;
    sf::RectangleShape    background_;

    sf::Clock elapsed_coldown_;
    sf::Clock bullet_clock_;
    sf::Time  bullet_cooldown_;

    //Initializer Functions
    void InitKeybinds();
    void InitTextures();
    void InitBackground();
    void InitPlayer();
    void InitAsteroids();
    void FireBullet(Ship* s);
};

#endif // !GAMESTATE_H_
