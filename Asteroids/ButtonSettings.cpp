#include "stdafx.h"
#include "ButtonSettings.h"

ButtonSettings::ButtonSettings()
{
    //button
    btn_txt_idle_   = sf::Color(255, 0, 0, 200);
    btn_txt_hover_  = sf::Color(255, 102, 102, 250);
    btn_txt_active_ = sf::Color(204, 0, 0, 50);
    btn_bg_idle_    = sf::Color(255, 0, 0, 0);
    btn_bg_hover_   = sf::Color(255, 102, 102, 0);
    btn_bg_active_  = sf::Color(204, 0, 0, 0);

    //dropdown list button
    btn_ddl_txt_idle_   = sf::Color(255, 0, 0, 255);
    btn_ddl_txt_hover_  = sf::Color(250, 215, 215, 200);
    btn_ddl_txt_active_ = sf::Color(250, 255, 255, 100);
    btn_ddl_bg_idle_    = sf::Color(0, 0, 0, 200);
    btn_ddl_bg_hover_   = sf::Color(0, 0, 0, 200);
    btn_ddl_bg_active_  = sf::Color(20, 20, 20, 200);
}

ButtonSettings::~ButtonSettings()
{
}

void ButtonSettings::SaveToFile(std::string path)
{
    std::ofstream ofs(path);

    if (ofs.is_open())
    {
        ofs << btn_txt_idle_.toInteger() << '\n';
        ofs << btn_txt_hover_.toInteger() << '\n';
        ofs << btn_txt_active_.toInteger() << '\n';
        ofs << btn_bg_idle_.toInteger() << '\n';
        ofs << btn_bg_hover_.toInteger() << '\n';
        ofs << btn_bg_active_.toInteger() << '\n';
        ofs << btn_ddl_txt_idle_.toInteger() << '\n';
        ofs << btn_ddl_txt_hover_.toInteger() << '\n';
        ofs << btn_ddl_txt_active_.toInteger() << '\n';
        ofs << btn_ddl_bg_idle_.toInteger() << '\n';
        ofs << btn_ddl_bg_hover_.toInteger() << '\n';
        ofs << btn_ddl_bg_active_.toInteger() << '\n';
    }

    ofs.close();
}

void ButtonSettings::LoadFromFile(std::string path)
{
    std::string color = "";

    std::ifstream ifs(path);
    if (ifs.is_open())
    {
        ifs >> color;
        btn_txt_idle_ = ToColor(color);
        ifs >> color;
        btn_txt_hover_= ToColor(color);
        ifs >> color;
        btn_txt_active_ = ToColor(color);
        ifs >> color;
        btn_bg_idle_ = ToColor(color);
        ifs >> color;
        btn_bg_hover_ = ToColor(color);
        ifs >> color;
        btn_bg_active_ = ToColor(color);
        ifs >> color;
        btn_ddl_txt_idle_ = ToColor(color);
        ifs >> color;
        btn_ddl_txt_hover_ = ToColor(color);
        ifs >> color;
        btn_ddl_txt_active_ = ToColor(color);
        ifs >> color;
        btn_ddl_bg_idle_ = ToColor(color);
        ifs >> color;
        btn_ddl_bg_hover_ = ToColor(color);
        ifs >> color;
        btn_ddl_bg_active_ = ToColor(color);
    }
    
    ifs.close();
}

//Convert string to sf::Color(R,G,B,A)
sf::Color ButtonSettings::ToColor(std::string color)
{
    uint32_t color32 = 0;

    for (int i = 0; i < color.length(); ++i)
    {
        color32 *= 10;
        color32 += (int)color[ i ] - 48;
    }
    uint8_t alpha = color32 & 0xff;
    uint8_t blue  = (color32 >> 8) & 0xff;
    uint8_t green = (color32 >> 16) & 0xff;
    uint8_t red   = (color32 >> 24) & 0xff;

    return sf::Color(red, green, blue, alpha);
}
