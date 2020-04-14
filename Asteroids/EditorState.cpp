#include "EditorState.h"

//Constructors / Destructors
EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys,
                             std::stack<State*>* states)
        : State(window, supported_keys, states)
{
    InitVariables();
    InitBackground();
    InitFonts();
    InitKeybinds();
    InitButtons();
}

EditorState::~EditorState()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
}

//Initializer functions
void EditorState::InitVariables()
{
}

void EditorState::InitBackground()
{
}

void EditorState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::EDITORSTATE::COULD_NOT_LOAD_FONT");
    }
}

void EditorState::InitKeybinds()
{
    std::ifstream ifs("config/editorstate_keybinds.ini");
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

void EditorState::InitButtons()
{
}

//Update functions
void EditorState::UpdateInput(const float& delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
        EndState();
}

void EditorState::UpdateButtons()
{
    /*Update all buttons in the state and handle functionality*/
    for (auto& it : buttons_)
    {
        it.second->Update(mouse_pos_view_);
    }
}

void EditorState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    UpdateButtons();
}

//Render functions
void EditorState::RenderButtons(sf::RenderTarget* target)
{
    for (auto& it : buttons_)
    {
        it.second->Render(target);
    }
}

void EditorState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }

    RenderButtons(target);

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
