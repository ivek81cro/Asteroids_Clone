#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    title_                              = "Asteroids Clone C++ SFML - NWP Project";
    resolution_                         = sf::VideoMode::getDesktopMode();
    fullscreen_                         = true;
    frame_rate_limit_                   = 120;
    v_sync_                             = false;
    context_settings_.antialiasingLevel = 0;
    video_modes_                        = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{
}

//Functions
void GraphicsSettings::SaveToFile(std::string path)
{
    std::ofstream ofs(path);

    if (ofs.is_open())
    {
        ofs << title_ << '\n';
        ofs << resolution_.width << " " << resolution_.height << '\n';
        ofs << fullscreen_ << '\n';
        ofs << frame_rate_limit_ << '\n';
        ofs << v_sync_ << '\n';
        ofs << context_settings_.antialiasingLevel << '\n';
    }

    ofs.close();
}

void GraphicsSettings::LoadFromFile(std::string path)
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
