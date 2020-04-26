#include "stdafx.h"
#include "MainMenuState.h"

//Constructors / Destructors
MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data)
{
    InitVariables();
    InitBackground();
    InitFonts();
    InitKeybinds();
    InitButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
}

//Initializer functions
void MainMenuState::InitVariables()
{
}

void MainMenuState::InitBackground()
{
    background_.setSize(
        sf::Vector2f(static_cast<float>(window_->getSize().x), static_cast<float>(window_->getSize().y)));

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
}

void MainMenuState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
}

void MainMenuState::InitKeybinds()
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

void MainMenuState::InitButtons()
{

    buttons_[ "GAME_STATE" ] = new gui::Button(
        PercToPixelX(40.23f), PercToPixelY(30.52f), PercToPixelX(19.53f), PercToPixelY(6.94f), &font_, "New game",
        CalcFontSIze(), sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "SETTINGS_STATE" ] = new gui::Button(
        PercToPixelX(40.23f), PercToPixelY(44.40f), PercToPixelX(19.53f), PercToPixelY(6.94f), &font_, "Settings",
        CalcFontSIze(), sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "EXIT_STATE" ] = new gui::Button(
        PercToPixelX(40.23f), PercToPixelY(58.28f), PercToPixelX(19.53f), PercToPixelY(6.94f), &font_, "Quit",
        CalcFontSIze(), sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));
}

//Update functions
void MainMenuState::UpdateInput(const float& delta)
{
}

void MainMenuState::UpdateButtons()
{
    /*Update all buttons in the state and handle functionality*/
    for (auto& it : buttons_)
    {
        it.second->Update(mouse_pos_view_);
    }

    //New game
    if (buttons_[ "GAME_STATE" ]->IsPressed())
    {
        states_->push(new GameState(state_data_));
    }

     //Settings
    if (buttons_[ "SETTINGS_STATE" ]->IsPressed())
    {
        states_->push(new SettingsState(state_data_));
    }

    //Quit game
    if (buttons_[ "EXIT_STATE" ]->IsPressed())
    {
        EndState();
    }
}

void MainMenuState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    UpdateButtons();
}

//Render functions
void MainMenuState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : buttons_)
    {
        it.second->Render(target);
    }
}

void MainMenuState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }
    target->draw(background_);

    RenderButtons(*target);

    ////Mouse coordinates for testing
    //sf::Text mouse_text;
    //mouse_text.setPosition(mouse_pos_view_.x, mouse_pos_view_.y - 50);
    //mouse_text.setFont(font_);
    //mouse_text.setCharacterSize(12);
    //std::stringstream ss;
    //ss << mouse_pos_view_.x << " " << mouse_pos_view_.y;
    //mouse_text.setString(ss.str());

    //target->draw(mouse_text);
}
