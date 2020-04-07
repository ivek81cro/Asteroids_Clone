#ifndef STATE_H_
#define STATE_H_

#include "Entity.h"

class State
{
  public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys, std::stack<State*>* states);
    virtual ~State();

    const bool& GetQuit() const;

    virtual void CheckForQuit();

    virtual void EndState()                                 = 0;
    virtual void UpdateMousePositions();
    virtual void UpdateInput(const float& delta)            = 0;
    virtual void Update(const float& delta)                 = 0;
    virtual void Render(sf::RenderTarget* target = nullptr) = 0;

  protected:
    std::stack<State*>*         states_;
    sf::RenderWindow*           window_;
    std::map<std::string, int>* supported_keys_;
    std::map<std::string, int>  keybinds_;
    bool                        quit_;

    //Mouse position
    sf::Vector2i mouse_pos_screen_;
    sf::Vector2i mouse_pos_window_;
    sf::Vector2f mouse_pos_view_;

    //Resources
    std::vector<sf::Texture> textures_;

    //Functions
    virtual void InitKeybinds() = 0;

    private:
};

#endif // !STATE_H_
