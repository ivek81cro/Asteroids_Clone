#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys,
                             std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitVariables();
    InitBackground();
    InitFonts();
    InitKeybinds();
    InitButtons();
}

SettingsState::~SettingsState()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }

    delete ddl_;
}

//Initializer functions
void SettingsState::InitVariables()
{
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
    sf::Vector2f position;
    position.x = window_->getSize().x / 2.f - 125.f;
    position.y = window_->getSize().y / 2.f - 25.f;

    buttons_[ "EXIT_STATE" ] =
        new gui::Button(position.x, position.y + 25.f, 250, 50, &font_, "Quit", 50, sf::Color(255, 0, 0, 200),
                   sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50), sf::Color(255, 0, 0, 0),
                   sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    std::string li[] = {
        "sfds", "sfdsdf", "dfdgf", "efsfd", "sfdsdfs",
    };
    ddl_ = new gui::DropDownList(100, 100, 200, 50, font_, li, 5);
}

//Accessor

//Functions
void SettingsState::UpdateInput(const float& delta)
{
}

void SettingsState::UpdateButtons()
{
    /*Update all buttons in the state and handle functionality*/
    for (auto& it : buttons_)
    {
        it.second->Update(mouse_pos_view_);
    }

    //Quit game
    if (buttons_[ "EXIT_STATE" ]->IsPressed())
    {
        EndState();
    }
}

void SettingsState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    UpdateButtons();

    ddl_->Update(mouse_pos_view_, delta);
}

void SettingsState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : buttons_)
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

    ddl_->Render(*target);

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
