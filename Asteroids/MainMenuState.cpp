#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys,
                             std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitFonts();
    InitKeybinds();
    InitButtons();

    background_.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background_.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
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
    buttons_[ "GAME_STATE" ] = new Button(100, 100, 150, 50, &font_, "New game", sf::Color(70, 70, 70, 200),
                                          sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    buttons_[ "EXIT_STATE" ] = new Button(100, 300, 150, 50, &font_, "Quit", sf::Color(100, 100, 100, 200),
                                          sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

void MainMenuState::UpdateInput(const float& delta)
{
    CheckForQuit();
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
        states_->push(new GameState(window_, supported_keys_, states_));
    }

    //Quit game
    if (buttons_[ "EXIT_STATE" ]->IsPressed())
    {
        quit_ = true;
    }
}

void MainMenuState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    UpdateButtons();
}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
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

    RenderButtons(target);
}
