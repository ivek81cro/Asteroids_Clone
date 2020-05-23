#ifndef BUTTONSETTINGS_H_
#define BUTTONSETTINGS_H_

class ButtonSettings
{
  public:
    ButtonSettings();
    virtual ~ButtonSettings();

    //Button colors
    sf::Color btn_txt_idle_;
    sf::Color btn_txt_hover_;
    sf::Color btn_txt_active_;
    sf::Color btn_bg_idle_;
    sf::Color btn_bg_hover_;
    sf::Color btn_bg_active_;

    //DDL button colors
    sf::Color btn_ddl_txt_idle_;
    sf::Color btn_ddl_txt_hover_;
    sf::Color btn_ddl_txt_active_;
    sf::Color btn_ddl_bg_idle_;
    sf::Color btn_ddl_bg_hover_;
    sf::Color btn_ddl_bg_active_;

    //Functions
    void SaveToFile(std::string path);
    void LoadFromFile(std::string path);

    private:
    sf::Color ToColor(std::string str);
};

#endif