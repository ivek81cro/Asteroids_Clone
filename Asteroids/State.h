#ifndef STATE_H_
#define STATE_H_

#include "Asteroid.h"
#include "Bullet.h"
#include "Entity.h"
#include "GraphicsSettings.h"
#include "Ship.h"
#include "EnemyUfo.h"
#include "DropLife.h"
#include "EnumsState.h"
#include "FilePaths.h"

class State;

/**
    Class container for data needed in states
*/
class StateData
{
  public:
    StateData(){};

    //Variables
    sf::RenderWindow*                   window_;
    GraphicsSettings*                   gfx_settings_;
    std::map<SupportedKeys, int>*         supported_keys_;
    std::stack<std::unique_ptr<State>>* states_;
    sf::Event*                          event_;
    std::string*                        path_game_state_keys_;
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
    void EndState();
    void PauseState();
    void UnpauseState();

    virtual void UpdateMousePositions();
    virtual void UpdateKeytime(const float& delta);
    virtual void UpdateInput(const float& delta)            = 0;
    virtual void Update(const float& delta)                 = 0;
    virtual void Render(sf::RenderTarget* target = nullptr) = 0;

  protected:
    StateData*                          state_data_;
    std::stack<std::unique_ptr<State>>* states_;
    sf::RenderWindow*                   window_;
    std::map<SupportedKeys, int>*       supported_keys_;
    std::map<Keybinds, int>             keybinds_;
    bool                                quit_;
    bool                                paused_;
    float                               keytime_;
    float                               keytime_max_;

    //Mouse position
    sf::Vector2i mouse_pos_screen_;
    sf::Vector2i mouse_pos_window_;
    sf::Vector2f mouse_pos_view_;

    //Resources
    std::map<Textures, sf::Texture> textures_;

    //Functions
    virtual void InitKeybinds() = 0;

    Keybinds      SelectEnumKeybinds(std::string key);
    SupportedKeys SelectEnumSupportedKeys(std::string key);

  private:
};

#endif // !STATE_H_
