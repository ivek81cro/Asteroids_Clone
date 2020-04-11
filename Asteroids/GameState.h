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
    Ship* player_;

    //Initializer Functions
    void InitKeybinds();
    void InitTextures();
    void InitPlayer();
};

#endif // !GAMESTATE_H_
