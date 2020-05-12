#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
        : State(state_data)
{
    InitVariables();
    InitFonts();
    InitKeybinds();
    InitGui();
}

SettingsState::~SettingsState()
{
}

//Initializer functions
void SettingsState::InitVariables()
{
    v_modes_ = sf::VideoMode::getFullscreenModes();

    key_configs_.insert(std::make_pair("Arrows","Config/gamestate_keybinds.ini"));
    key_configs_.insert(std::make_pair("WASD keys","Config/gamestate_keybinds_wasd.ini"));
}

void SettingsState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
}

void SettingsState::InitKeybinds()
{
    std::ifstream ifs("config/mainmenustate_keybinds.ini");
    if (ifs.is_open())
    {
        std::string key  = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            keybinds_[ key ] = supported_keys_->at(key2);
        }
    }
    ifs.close();
}

void SettingsState::InitGui()
{
    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    InitBackground(vm);
    InitButtons(vm);
    InitDropdownList(vm);
    InitText(vm);
}

void SettingsState::InitBackground(const sf::VideoMode& vm)
{
    //Backround
    background_.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
}

void SettingsState::InitButtons(const sf::VideoMode& vm)
{
    //Buttons
    float width  = gui::PercToPixelX(19.53f, vm);
    float height = gui::PercToPixelY(6.94f, vm);

    buttons_[ "BACK" ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(90.19f, vm), width, height,
                                         &font_, "Back", gui::CalcFontSIze(vm, 60), sf::Color(255, 0, 0, 200),
                                         sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                                         sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));

    buttons_[ "APPLY" ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(82.28f, vm), width, height, 
                                           &font_, "Apply", gui::CalcFontSIze(vm, 60), sf::Color(255, 0, 0, 200), 
                                           sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                                           sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));
}

void SettingsState::InitDropdownList(const sf::VideoMode& vm)
{
    //Drop down list
    //Resolution
    unsigned int             default_mode = 0;
    std::vector<std::string> modes_str;
    auto                     it = v_modes_.begin();
    int                      i  = 0;

    for (it = v_modes_.begin(), i = 0; it != v_modes_.end(); ++it, ++i)
    {
        modes_str.push_back(std::to_string((*it).width) + 'x' + std::to_string((*it).height));
        if (state_data_->gfx_settings_->resolution_.width == (*it).width &&
            state_data_->gfx_settings_->resolution_.height == (*it).height)
            default_mode = i;
    }

    ddl_[ "RESOLUTION" ] = std::unique_ptr<gui::DropDownList>(
        new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(13.89f, vm), gui::PercToPixelX(15.f, vm),
                              gui::PercToPixelY(7.f, vm), font_, vm, modes_str.data(), 
                              static_cast<int>(modes_str.size()), default_mode));

    default_mode = 0;

    std::vector<std::string> fulscreen_str;
    fulscreen_str.push_back("OFF");
    fulscreen_str.push_back("ON");

    if (state_data_->gfx_settings_->fullscreen_)
        default_mode = 1;

    ddl_[ "FULLSCREEN" ] = std::unique_ptr<gui::DropDownList>(
        new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(23.f, vm), gui::PercToPixelX(15.f, vm),
                              gui::PercToPixelY(7.f, vm), font_, vm, fulscreen_str.data(),
                              static_cast<int>(fulscreen_str.size()), default_mode));
    default_mode         = 0;

    //V-Sync list
    std::vector<std::string> v_sync_str;
    v_sync_str.push_back("OFF");
    v_sync_str.push_back("ON");

    if (state_data_->gfx_settings_->v_sync_)
        default_mode = 1;

    ddl_[ "VSYNC" ] = std::unique_ptr<gui::DropDownList>(
        new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(32.8f, vm),
                              gui::PercToPixelX(15.f, vm), gui::PercToPixelY(7.f, vm), font_, vm,
                              v_sync_str.data(), static_cast<int>(v_sync_str.size()), default_mode));
    default_mode    = 0;

    //Antialiasing list
    std::vector<std::string> antialiasnig_str;
    antialiasnig_str.push_back("0x");
    antialiasnig_str.push_back("1x");
    antialiasnig_str.push_back("2x");
    antialiasnig_str.push_back("4x");

    default_mode           = state_data_->gfx_settings_->context_settings_.antialiasingLevel;

    ddl_[ "ANTIALIASING" ] = std::unique_ptr<gui::DropDownList>(
        new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(42.f, vm),
                                                   gui::PercToPixelX(15.f, vm), gui::PercToPixelY(7.f, vm), font_, vm,
                                                   antialiasnig_str.data(), static_cast<int>(antialiasnig_str.size()), default_mode));
    default_mode           = 0;

    //Keys configuration list
    std::vector<std::string> keys_path_str;
    auto                     it2 = key_configs_.begin();
    i                            = 0;

    for (it2 = key_configs_.begin(), i = 0; it2 != key_configs_.end(); ++it2, ++i)
    {
        keys_path_str.push_back((*it2).first);
        if (!state_data_->path_game_state_keys_->compare((*it2).second))
            default_mode = i;
    }

    ddl_[ "KEYSCONFIG" ] = std::unique_ptr<gui::DropDownList>(
        new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(52.f, vm),
                                                 gui::PercToPixelX(15.f, vm), gui::PercToPixelY(7.f, vm), font_, vm,
                                                 keys_path_str.data(), static_cast<int>(keys_path_str.size()), default_mode));
}

void SettingsState::InitText(const sf::VideoMode& vm)
{
    //Text
    options_text_.setFont(font_);
    options_text_.setPosition(sf::Vector2f(gui::PercToPixelX(7.82f, vm), gui::PercToPixelY(13.89f, vm)));
    options_text_.setCharacterSize(gui::CalcFontSIze(vm, 70));
    options_text_.setFillColor(sf::Color(250, 0, 0, 200));
    options_text_.setLineSpacing(2);

    options_text_.setString("Resolution \nFullscreen \nVsync \nAntialiasing \nKeys config \n");

    warning_text_.setFont(font_);
    warning_text_.setPosition(sf::Vector2f(gui::PercToPixelX(5.f, vm), gui::PercToPixelY(75.f, vm)));
    warning_text_.setCharacterSize(gui::CalcFontSIze(vm, 70));
    warning_text_.setFillColor(sf::Color(250, 0, 0, 200));
    warning_text_.setOutlineThickness(3);
    warning_text_.setOutlineColor(sf::Color(255, 255, 255, 255));

    warning_text_.setString("");
}

//Functions
void SettingsState::ResetGui()
{
    buttons_.clear();

    ddl_.clear();

    InitGui();
}

void SettingsState::UpdateInput(const float& delta)
{
}

void SettingsState::UpdateGui(const float& delta)
{
    /*Update all buttons in the state and handle functionality*/    

    //Buttons
    for (auto& it : buttons_)
    {
        it.second->Update(mouse_pos_view_);
    }

    //Button functionality
    //Quit settings
    if (buttons_[ "BACK" ]->IsPressed() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
    {
        EndState();
    }

    //Apply
    if (buttons_[ "APPLY" ]->IsPressed())
    {
        if (ddl_[ "RESOLUTION" ]->GetToggle())
            state_data_->gfx_settings_->resolution_ = 
            v_modes_[ ddl_[ "RESOLUTION" ]->GetActiveElementId() ];

        //Get fullscreen toggle
        if (ddl_[ "FULLSCREEN" ]->GetToggle())
            state_data_->gfx_settings_->fullscreen_ = ddl_[ "FULLSCREEN" ]->GetActiveElementId();

        //Get v-sync toggle
        if (ddl_[ "VSYNC" ]->GetToggle())
            state_data_->gfx_settings_->v_sync_ = ddl_[ "VSYNC" ]->GetActiveElementId();

        //Get antialiasing toggle
        if (ddl_[ "ANTIALIASING" ]->GetToggle())
            state_data_->gfx_settings_->context_settings_.antialiasingLevel =
            ddl_[ "ANTIALIASING" ]->GetActiveElementId();

        //Get key config toggle
        if (ddl_[ "KEYSCONFIG" ]->GetToggle())
            state_data_->gfx_settings_->path_game_state_keys_ = 
            key_configs_.at( ddl_[ "KEYSCONFIG" ]->GetActiveElementText());

        state_data_->gfx_settings_->SaveToFile("Config/graphics.ini");
        warning_text_.setString("Restart game for changes to take effect.");
    }

    //Dropdown lists
    for (auto& it : ddl_)
    {
        it.second->Update(mouse_pos_view_, delta);
    }

    //Dropdown lists functionality
}

void SettingsState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);
    UpdateKeytime(delta);
    UpdateGui(delta);
}

void SettingsState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : buttons_)
    {
        it.second->Render(target);
    }

    //Prevent overlap of ddl's items
    bool exists_active = false;
    for (auto& it : ddl_)
    {
        if (it.second->IsActive())
        {
            it.second->Render(target);
            exists_active = true;
            break;
        }
    }

    if (!exists_active)
    {
        for (auto& it : ddl_)
        {
            it.second->Render(target);
        }
    }

}

void SettingsState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }
    target->draw(background_);

    RenderButtons(*target);

    target->draw(options_text_);
    target->draw(warning_text_);

    //Mouse coordinates for testing
    /*sf::Text mouse_text;
    mouse_text.setPosition(mouse_pos_view_.x, mouse_pos_view_.y - 50);
    mouse_text.setFont(font_);
    mouse_text.setCharacterSize(12);
    std::stringstream ss;
    ss << mouse_pos_view_.x << " " << mouse_pos_view_.y;
    mouse_text.setString(ss.str());

    target->draw(mouse_text);*/
}