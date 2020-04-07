#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"

class GameState : public State
{
  public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
    virtual ~GameState();

    void EndState();

    void UpdateInput(const float& delta);
    void Update(const float& delta);
    void Render(sf::RenderTarget* target = nullptr);

  private:
    Entity player_;

    //Functions
    void InitKeybinds();
};

#endif // !GAMESTATE_H_
