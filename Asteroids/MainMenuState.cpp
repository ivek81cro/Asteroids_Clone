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
}

//Initializer functions
void MainMenuState::InitVariables()
{
}

/**
    Load font
*/
void MainMenuState::InitFonts()
{
    try
    {
        if (!font_.loadFromFile(PATH_FILE_FONTS))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_FONT_FILE);
    }
}

/**
    Load keybinds
*/
void MainMenuState::InitKeybinds()
{
    std::ifstream ifs(PATH_FILE_KEYBINDS_MAIN_MENU);

    if (ifs.is_open())
    {
        std::string key  = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            Keybind_e      key_e  = SelectEnumKeybinds(key);
            SupportedKey_e key2_e = SelectEnumSupportedKeys(key2);

            if (key_e != Keybind_e::Unknown && key2_e != SupportedKey_e::Unsupported)
                keybinds_[ key_e ] = supported_keys_->at(key2_e);
        }
    }
    ifs.close();
}

/**
    Initialize GUI
*/
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

    try
    {
        if (!textures_[ Texture_e::Background_texture ].loadFromFile(PATH_TEXTURE_BACKGROUND_MAIN))
        {
            throw XFileError(ERRORMESSAGE_ERROR_READING_FILE);
        }
    }
    catch (XError& error)
    {
        error.LogError(ERRORMESSAGE_ERROR_READING_BACKGROUND_TEXTURE_FILE);
    }

    background_.setTexture(&textures_[ Texture_e::Background_texture ]);

    //Buttons
    buttons_[ Buttons::Game_state ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(20.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "New game", gui::CalcFontSize(vm, 40),
                        sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));

    buttons_[ Buttons::Settings_state ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(35.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "Settings", gui::CalcFontSize(vm, 40),
                        sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));

    buttons_[ Buttons::Score_state ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(50.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "High Scores", gui::CalcFontSize(vm, 40),
                        sf::Color(255, 0, 0, 200), sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                        sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));

    buttons_[ Buttons::Exit_state ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(65.f, vm), gui::PercToPixelX(19.53f, vm),
                        gui::PercToPixelY(6.94f, vm), &font_, "Quit", gui::CalcFontSize(vm, 40), sf::Color(255, 0, 0, 200),
                        sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50), sf::Color(255, 0, 0, 0),
                        sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));
}

//Update functions
void MainMenuState::ResetGui()
{

    buttons_.clear();
    InitGui();
}

void MainMenuState::UpdateInput(const float& delta)
{
}

/**
    Update buttons
*/
void MainMenuState::UpdateButtons()
{
    /*Update all buttons in the state and handle functionality*/
    for (auto& it : buttons_)
    {
        it.second->Update(mouse_pos_view_);
    }

    //New game
    if (buttons_[ Buttons::Game_state ]->IsPressed())
    {
        states_->push(std::unique_ptr<State>(new GameState(state_data_)));
    }

     //Settings
    if (buttons_[ Buttons::Settings_state ]->IsPressed())
    {
        states_->push(std::unique_ptr<State>(new SettingsState(state_data_)));
    }

    //High scores
    if (buttons_[ Buttons::Score_state ]->IsPressed())
    {
        states_->push(std::unique_ptr<State>(new ScoreState(state_data_, NULL, false)));
    }

    //Quit game
    if (buttons_[ Buttons::Exit_state ]->IsPressed())
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
