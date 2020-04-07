#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys,
                             std::stack<State*>* states)
        : State(window, supported_keys, states)
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

    if (!background_texture_.loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&background_texture_);
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
    sf::Vector2f position;
    position.x = window_->getSize().x / 2.f - 125.f;
    position.y = window_->getSize().y / 2.f - 25.f;

    buttons_[ "GAME_STATE" ] = new Button(position.x, position.y-200.f, 250, 50, &font_, "New game", sf::Color(255, 0, 0, 200),
                                          sf::Color(255, 102, 102, 200), sf::Color(204, 0, 0, 200));

    buttons_[ "SETTINGS" ] = new Button(position.x, position.y - 125.f, 250, 50, &font_, "Settings", sf::Color(255, 0, 0, 200),
                   sf::Color(255, 102, 102, 200), sf::Color(204, 0, 0, 200));

    buttons_[ "EXIT_STATE" ] = new Button(position.x, position.y-50.f, 250, 50, &font_, "Quit", sf::Color(255, 0, 0, 200),
                                          sf::Color(255, 102, 102, 200), sf::Color(204, 0, 0, 200));
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
        states_->push(new GameState(window_, supported_keys_, states_));
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

    //Mouse coordinates for testing
    sf::Text mouse_text;
    mouse_text.setPosition(mouse_pos_view_.x, mouse_pos_view_.y -50);
    mouse_text.setFont(font_);
    mouse_text.setCharacterSize(12);
    std::stringstream ss;
    ss << mouse_pos_view_.x << " " << mouse_pos_view_.y;
    mouse_text.setString(ss.str());

    target->draw(mouse_text);
}
