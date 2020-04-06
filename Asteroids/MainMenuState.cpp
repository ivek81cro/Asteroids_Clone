#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys)
        : State(window, supported_keys)
{
    InitFonts();
    InitKeybinds();

    game_state_button_ = new Button(100,100,150,50,&font_, "New game",
        sf::Color(70, 70, 70, 200), 
        sf::Color(150,150,150, 200), 
        sf::Color(20,20,20, 200));

    background_.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background_.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
    delete game_state_button_;
}

void MainMenuState::EndState()
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
    std::ifstream ifs("config/gamestate_keybinds.ini");
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

void MainMenuState::UpdateInput(const float& delta)
{
    CheckForQuit();    
}

void MainMenuState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    game_state_button_->Update(mouse_pos_view_);
}

void MainMenuState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }
    target->draw(background_);

    game_state_button_->Render(target);
}
