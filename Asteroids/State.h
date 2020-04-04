#ifndef STATE_H_
#define STATE_H_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

class State
{
  public:
    State(sf::RenderWindow* window);
    virtual ~State();

    const bool& GetQuit() const;

    virtual void CheckForQuit();

    virtual void EndState()                                 = 0;
    virtual void UpdateKeybinds(const float& delta)         = 0;
    virtual void Update(const float& delta)                 = 0;
    virtual void Render(sf::RenderTarget* target = nullptr) = 0;

  private:
    sf::RenderWindow*        window_;
    std::vector<sf::Texture> textures_;
    bool                     quit_;
};

#endif // !STATE_H_
