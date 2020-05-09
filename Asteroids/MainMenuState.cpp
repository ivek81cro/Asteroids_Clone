#include "stdafx.h"
#include "MainMenuState.h"

//Constructors / Destructors
MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data)
{
    InitVariables();
    InitFonts();
    InitKeybinds();
    InitGui();
}

MainMenuState::~MainMenuState()
{
    auto it = buttons_.begin();
    for (it= buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
}

//Initializer functions
void MainMenuState::InitVariables()
{
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

void MainMenuState::InitGui()
{

    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    //Background
    background_.setSize(
        sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    
    //Darkened container behind buttons
    container_.setSize(
        sf::Vector2f(static_cast<float>(vm.width / 4.f), static_cast<float>(vm.height) - gui::PercToPixelY(20.f, vm)));
    container_.setFillColor(sf::Color(20, 20, 20, 200));
    container_.setPosition(static_cast<float>(vm.width / 2.f) - static_cast<float>(container_.getSize().x / 2.f),
                           gui::PercToPixelY(20.f, vm));

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background2.png"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);

    //Buttons
    buttons_[ "GAME_STATE" ] =
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(20.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "New game", gui::CalcFontSIze(vm, 40),
                        sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "SETTINGS_STATE" ] =
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(35.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "Settings", gui::CalcFontSIze(vm, 40),
                        sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "SCORE_STATE" ] =
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(50.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "High Scores", gui::CalcFontSIze(vm, 40),
                        sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    buttons_[ "EXIT_STATE" ] =
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(65.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "Quit", gui::CalcFontSIze(vm, 40), sf::Color(255, 0, 0, 200),
                        sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50), sf::Color(255, 0, 0, 0),
                        sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));
}

//Update functions
void MainMenuState::ResetGui()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
    buttons_.clear();

    InitGui();
}

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

    //High scores
    if (buttons_[ "SCORE_STATE" ]->IsPressed())
    {
        states_->push(new ScoreState(state_data_, NULL, false));
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
    target->draw(container_);

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
