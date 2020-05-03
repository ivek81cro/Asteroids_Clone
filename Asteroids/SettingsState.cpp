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
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }

    auto it2 = ddl_.begin();
    for (it2 = ddl_.begin(); it2 != ddl_.end(); ++it2)
    {
        delete it2->second;
    }
}

//Initializer functions
void SettingsState::InitVariables()
{
    v_modes_ = sf::VideoMode::getFullscreenModes();
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

    buttons_[ "BACK" ] = new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(90.19f, vm), width, height,
                                         &font_, "Back", gui::CalcFontSIze(vm, 60), sf::Color(255, 0, 0, 200),
                                         sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                                         sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "APPLY" ] = new gui::Button(
        gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(82.28f, vm), width, height, &font_, "Apply",
        gui::CalcFontSIze(vm, 60), sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));
}

void SettingsState::InitDropdownList(const sf::VideoMode& vm)
{
    //TODO Set active option as selected in ddl
    //Modes
    //TODO Try to fix this
    std::vector<std::string> fulscreen_str;
    fulscreen_str.push_back("OFF");
    fulscreen_str.push_back("ON");

    std::vector<std::string> v_sync_str;
    v_sync_str.push_back("OFF");
    v_sync_str.push_back("ON");

    std::vector<std::string> antialiasnig_str;
    antialiasnig_str.push_back("0x");
    antialiasnig_str.push_back("1x");
    antialiasnig_str.push_back("2x");
    antialiasnig_str.push_back("4x");

    unsigned                 default_mode = 0;
    std::vector<std::string> modes_str;
    for (auto& i : v_modes_)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
        if (state_data_->gfx_settings_->resolution_.width == i.width &&
            state_data_->gfx_settings_->resolution_.height == i.height)
            default_mode = modes_str.size() - 1;
    }

    //Drop down list
        //Resolution
    ddl_[ "RESOLUTION" ] = new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(13.89f, vm),
                                                 gui::PercToPixelX(20.78f, vm), gui::PercToPixelY(6.94f, vm), font_,
                                                 modes_str.data(), modes_str.size(), default_mode);

    default_mode = 0;

        //Fullscreen
    if (state_data_->gfx_settings_->fullscreen_)
        default_mode = 1;
    ddl_[ "FULLSCREEN" ] = new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(23.f, vm),
                                                 gui::PercToPixelX(20.78f, vm), gui::PercToPixelY(6.94f, vm), font_,
                                                 fulscreen_str.data(), fulscreen_str.size(), default_mode);
    default_mode         = 0;

        //V_Sync
    if (state_data_->gfx_settings_->v_sync_)
        default_mode = 1;
    ddl_[ "VSYNC" ] = new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(32.8f, vm),
                                            gui::PercToPixelX(20.78f, vm), gui::PercToPixelY(6.94f, vm), font_,
                                            v_sync_str.data(), v_sync_str.size(), default_mode);
    default_mode    = 0;

        //Antialiasing
    default_mode           = state_data_->gfx_settings_->context_settings_.antialiasingLevel;
    ddl_[ "ANTIALIASING" ] = new gui::DropDownList(gui::PercToPixelX(19.53f, vm), gui::PercToPixelY(42.f, vm),
                                                   gui::PercToPixelX(20.78f, vm), gui::PercToPixelY(6.94f, vm), font_,
                                                   antialiasnig_str.data(), antialiasnig_str.size(), default_mode);
}

void SettingsState::InitText(const sf::VideoMode& vm)
{
    //Text
    options_text_.setFont(font_);
    options_text_.setPosition(sf::Vector2f(gui::PercToPixelX(7.82f, vm), gui::PercToPixelY(13.89f, vm)));
    options_text_.setCharacterSize(gui::CalcFontSIze(vm, 70));
    options_text_.setFillColor(sf::Color(250, 0, 0, 200));
    options_text_.setLineSpacing(2);

    options_text_.setString("Resolution \nFullscreen \nVsync \nAntialiasing \n");

    warning_text_.setFont(font_);
    warning_text_.setPosition(sf::Vector2f(gui::PercToPixelX(7.82f, vm), gui::PercToPixelY(5.89f, vm)));
    warning_text_.setCharacterSize(gui::CalcFontSIze(vm, 70));
    warning_text_.setFillColor(sf::Color(250, 0, 0, 200));

    warning_text_.setString("");
}

//Functions
void SettingsState::ResetGui()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
    buttons_.clear();

    auto it2 = ddl_.begin();
    for (it2 = ddl_.begin(); it2 != ddl_.end(); ++it2)
    {
        delete it2->second;
    }
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
    //Quit game
    if (buttons_[ "BACK" ]->IsPressed())
    {
        EndState();
    }

    //Apply
    if (buttons_[ "APPLY" ]->IsPressed())
    {
        //Get selected resolution
        state_data_->gfx_settings_->resolution_ = v_modes_[ ddl_[ "RESOLUTION" ]->GetActiveElementId() ];

        //Get fullscreen toggle
        if (ddl_[ "FULLSCREEN" ]->GetActiveElementId())
            state_data_->gfx_settings_->fullscreen_ = true;
        else
            state_data_->gfx_settings_->fullscreen_ = false;

        //Get v-sync toggle
        if (ddl_[ "VSYNC" ]->GetActiveElementId())
            state_data_->gfx_settings_->v_sync_ = true;
        else
            state_data_->gfx_settings_->v_sync_ = false;

        //Get antialiasing toggle
        if (ddl_[ "ANTIALIASING" ]->GetActiveElementId())
            state_data_->gfx_settings_->context_settings_.antialiasingLevel =
                ddl_[ "ANTIALIASING" ]->GetActiveElementId();
        else
            state_data_->gfx_settings_->context_settings_.antialiasingLevel = 0;

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

    UpdateGui(delta);
}

void SettingsState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : buttons_)
    {
        it.second->Render(target);
    }

    //Prevent overlap of ddl's
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
    sf::Text mouse_text;
    mouse_text.setPosition(mouse_pos_view_.x, mouse_pos_view_.y - 50);
    mouse_text.setFont(font_);
    mouse_text.setCharacterSize(12);
    std::stringstream ss;
    ss << mouse_pos_view_.x << " " << mouse_pos_view_.y;
    mouse_text.setString(ss.str());

    target->draw(mouse_text);
}