#ifndef STATE_H_
#define STATE_H_

#include "Asteroid.h"
#include "Bullet.h"
#include "Entity.h"
#include "GraphicsSettings.h"
#include "ButtonSettings.h"
#include "Ship.h"
#include "EnemyUfo.h"
#include "DropLife.h"
#include "EnumsState.h"
#include "FilePaths.h"
#include "LogToFile.h"
#include "XFileError.h"
#include "Messages.h"

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
    ButtonSettings*                     btn_settings_;
    std::map<SupportedKey_e, int>*      supported_keys_;
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
    virtual void LogMessage(std::string& message);
    virtual void UpdateInput(const float& delta)            = 0;
    virtual void Update(const float& delta)                 = 0;
    virtual void Render(sf::RenderTarget* target = nullptr) = 0;

  protected:
    StateData*                          state_data_;
    std::stack<std::unique_ptr<State>>* states_;
    sf::RenderWindow*                   window_;
    std::map<SupportedKey_e, int>*       supported_keys_;
    std::map<Keybind_e, int>             keybinds_;
    bool                                quit_;
    bool                                paused_;
    float                               keytime_;
    float                               keytime_max_;

    //Mouse position
    sf::Vector2i mouse_pos_screen_;
    sf::Vector2i mouse_pos_window_;
    sf::Vector2f mouse_pos_view_;

    //Resources
    std::map<Texture_e, sf::Texture> textures_;

    //Functions
    virtual void InitKeybinds() = 0;

    Keybind_e      SelectEnumKeybinds(std::string key);
    SupportedKey_e SelectEnumSupportedKeys(std::string key);

  private:
};

#endif // !STATE_H_
