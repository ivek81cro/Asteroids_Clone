#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
        : State(state_data)
{
    InitVariables();
    InitBackground();
    InitFonts();
    InitKeybinds();
    InitButtons();
    InitText();
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

void SettingsState::InitBackground()
{
    background_.setSize(
        sf::Vector2f(static_cast<float>(window_->getSize().x), static_cast<float>(window_->getSize().y)));

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
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

void SettingsState::InitButtons()
{
    float x      = static_cast<float>(window_->getSize().x);
    float y      = static_cast<float>(window_->getSize().y);
    float width  = 250;
    float height = 50;

    buttons_[ "BACK" ] = new gui::Button(
        x / 2.f - width / 2.f, y - 100, width, height, &font_, "Back", 40, sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250),
        sf::Color(204, 0, 0, 50), sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "APPLY" ] = new gui::Button(
        x / 2.f - width / 2.f, y - 150, width, height, &font_, "Apply", 40, sf::Color(255, 0, 0, 200),
        sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50), sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), 
        sf::Color(204, 0, 0, 0));

    std::vector<std::string> modes_str;
    for (auto& i : v_modes_)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    ddl_[ "RESOLUTION" ] = new gui::DropDownList(250.f, 100.f, 200, 50, font_, modes_str.data(), modes_str.size());
}

void SettingsState::InitText()
{
    options_text_.setFont(font_);
    options_text_.setPosition(sf::Vector2f(100.f, 100.f));
    options_text_.setCharacterSize(30);
    options_text_.setFillColor(sf::Color(250, 0, 0, 200));
    options_text_.setLineSpacing(2);

    options_text_.setString("Resolution \nFullscreen \nVsync \nAntialiasing \n");
}

//Accessor

//Functions
void SettingsState::UpdateInput(const float& delta)
{
}

void SettingsState::UpdateButtons(const float& delta)
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
        //TEST
        state_data_->gfx_settings_->resolution_ = v_modes_[ ddl_[ "RESOLUTION" ]->GetActiveElementId() ];
        window_->create(state_data_->gfx_settings_->resolution_, state_data_->gfx_settings_->title_, sf::Style::Default);
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

    UpdateButtons(delta);
}

void SettingsState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : buttons_)
    {
        it.second->Render(target);
    }

    for (auto& it : ddl_)
    {
        it.second->Render(target);
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
