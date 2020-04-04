#ifndef _STATE_H_
#define _STATE_H_

#include <vector>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

class State
{
  private:
    sf::RenderWindow*        window;
    std::vector<sf::Texture> textures;
    bool                     quit;

  public:
    State(sf::RenderWindow* window);
    virtual ~State();

    const bool& getQuit() const;

    virtual void checkForQuit();

    virtual void endState()                                 = 0;
    virtual void updateKeybinds(const float& delta)         = 0;
    virtual void update(const float& delta)                 = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif // !_STATE_H_
