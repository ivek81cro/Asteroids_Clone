#ifndef GAME_H_
#define GAME_H_

#include "MainMenuState.h"

class Game
{
  private:
    class GraphicsSettings
    {
      public:
        GraphicsSettings()
        {
            title_                              = "UNINITIALIZED";
            resolution_                         = sf::VideoMode::getDesktopMode();
            fullscreen_                         = false;
            frame_rate_limit_                   = 120;
            v_sync_                             = false;
            context_settings_.antialiasingLevel = 0;
            video_modes_                        = sf::VideoMode::getFullscreenModes();
        }

        //Variables
        std::string                title_;
        sf::VideoMode              resolution_;
        bool                       fullscreen_;
        bool                       v_sync_;
        unsigned                   frame_rate_limit_;
        sf::ContextSettings        context_settings_;
        std::vector<sf::VideoMode> video_modes_;

        //Functions
        void SaveToFile(std::string path)
        {
            std::ofstream ofs(path);

            if (ofs.is_open())
            {
                ofs<< title_;
                ofs<<resolution_.width << " " << resolution_.height;
                ofs<<fullscreen_;
                ofs<<frame_rate_limit_;
                ofs<<v_sync_;
                ofs<<context_settings_.antialiasingLevel;
            }

            ofs.close();
        }
        void LoadFromFile(std::string path)
        {
            std::ifstream ifs(path);

            if (ifs.is_open())
            {
                std::getline(ifs, title_);
                ifs >> resolution_.width >> resolution_.height;
                ifs >> fullscreen_;
                ifs >> frame_rate_limit_;
                ifs >> v_sync_;
                ifs >> context_settings_.antialiasingLevel;
            }

            ifs.close();
        }
    };

  public:
    //Constructors/Destructors
    Game();
    virtual ~Game();

    //Functions

    //Regular functions
    void EndApplication();

    //Update
    void UpdateDelta();
    void UpdateSFMLEvents();
    void Update();

    //Render functions
    void Render();

    //Core function
    int Run();

  private:
    GraphicsSettings           gfx_settings_;
    sf::RenderWindow*          window_;
    sf::Event                  event_;

    sf::Clock clock_;
    float     delta_;

    std::stack<State*> states_;

    std::map<std::string, int> supported_keys_;

    //Inititalization
    void InitVariables();
    void InitGraphicsSettings();
    void InitWindow();
    void InitKeys();
    void InitStates();
};

#endif
