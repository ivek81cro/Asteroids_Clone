#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "State.h"
class GameState : public State
{
  private:
  public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    void endState();

    void updateKeybinds(const float& delta);
    void update(const float& delta);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !_GAMESTATE_H_
