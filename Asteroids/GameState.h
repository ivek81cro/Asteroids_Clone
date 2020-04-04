#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"
class GameState : public State
{
  public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    void EndState();

    void UpdateKeybinds(const float& delta);
    void Update(const float& delta);
    void Render(sf::RenderTarget* target = nullptr);

  private:
};

#endif // !GAMESTATE_H_
