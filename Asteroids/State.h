#ifndef STATE_H_
#define STATE_H_

#include "Asteroid.h"
#include "Bullet.h"
#include "Entity.h"
#include "GraphicsSettings.h"
#include "Ship.h"

class State;

class StateData
{
  public:
    StateData(){};

    //Variables
    sf::RenderWindow*           window_;
    GraphicsSettings*           gfx_settings_;
    std::map<std::string, int>* supported_keys_;
    std::stack<State*>*         states_;
};

class State
{
  public:
    State(StateData* state_data);
    virtual ~State();

    //Accessor
    const bool& GetQuit() const;
    const bool  GetKeytime();

    //Functions
    const float PercToPixelX(const float perc) const;
    const float PercToPixelY(const float perc) const;
    const unsigned CalcFontSIze() const ;

    void EndState();
    void PauseState();
    void UnpauseState();

    virtual void UpdateMousePositions();
    virtual void UpdateKeytime(const float& delta);
    virtual void UpdateInput(const float& delta)            = 0;
    virtual void Update(const float& delta)                 = 0;
    virtual void Render(sf::RenderTarget* target = nullptr) = 0;

  protected:
    StateData*                  state_data_;
    std::stack<State*>*         states_;
    sf::RenderWindow*           window_;
    std::map<std::string, int>* supported_keys_;
    std::map<std::string, int>  keybinds_;
    bool                        quit_;
    bool                        paused_;
    float                       keytime_;
    float                       keytime_max_;

    //Mouse position
    sf::Vector2i mouse_pos_screen_;
    sf::Vector2i mouse_pos_window_;
    sf::Vector2f mouse_pos_view_;

    //Resources
    std::map<std::string, sf::Texture> textures_;

    //Functions
    virtual void InitKeybinds() = 0;

  private:
};

#endif // !STATE_H_
