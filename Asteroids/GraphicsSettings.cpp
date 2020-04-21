#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    title_                              = "UNINITIALIZED";
    resolution_                         = sf::VideoMode::getDesktopMode();
    fullscreen_                         = false;
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
        ofs << title_;
        ofs << resolution_.width << " " << resolution_.height;
        ofs << fullscreen_;
        ofs << frame_rate_limit_;
        ofs << v_sync_;
        ofs << context_settings_.antialiasingLevel;
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