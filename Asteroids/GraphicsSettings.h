#ifndef GRAPHICSSETTINGS_H_
#define GRAPHICSSETTINGS_H_


class GraphicsSettings
{
  public:
    GraphicsSettings();
    virtual ~GraphicsSettings();

    //Variables
    std::string                title_;
    sf::VideoMode              resolution_;
    bool                       fullscreen_;
    bool                       v_sync_;
    unsigned                   frame_rate_limit_;
    sf::ContextSettings        context_settings_;
    std::vector<sf::VideoMode> video_modes_;

    //Functions
    void SaveToFile(std::string path);
    void LoadFromFile(std::string path);
};

#endif