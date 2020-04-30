#include "stdafx.h"
#include "ScoreState.h"

ScoreState::ScoreState(StateData* state_data, const int& score)
        : State(state_data)
{
    InitFonts();
    InitKeybinds();
    ReadScoresFile();
    InitGui();
}

ScoreState::~ScoreState()
{
    auto it = buttons_.begin();
    for (it = buttons_.begin(); it != buttons_.end(); ++it)
    {
        delete it->second;
    }
}

void ScoreState::InitFonts()
{
    if (!font_.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
}

void ScoreState::InitGui()
{
    const sf::VideoMode& vm = state_data_->gfx_settings_->resolution_;

    //Backround
    background_.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);

    //Buttons
    float width  = gui::PercToPixelX(19.53f, vm);
    float height = gui::PercToPixelY(6.94f, vm);

    buttons_[ "BACK" ] = new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(90.19f, vm), width, height,
                                         &font_, "Back", gui::CalcFontSIze(vm, 60), sf::Color(255, 0, 0, 200),
                                         sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                                         sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));

    //Text
    text_.setFont(font_);
    text_.setPosition(sf::Vector2f(gui::PercToPixelX(7.82f, vm), gui::PercToPixelY(13.89f, vm)));
    text_.setCharacterSize(gui::CalcFontSIze(vm, 70));
    text_.setFillColor(sf::Color(250, 0, 0, 200));
    text_.setLineSpacing(2);

    std::string score_string = "High scores:\n";

    for (auto& score : scores_)
    {
        score_string.append(score.first);
        score_string.append("\t");
        score_string.append(std::to_string(score.second));
        score_string.append("\n");
    }

    text_.setString(score_string);
}

void ScoreState::InitKeybinds()
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

void ScoreState::UpdateInput(const float& delta)
{
}

void ScoreState::UpdateGui(const float& delta)
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
}

void ScoreState::Update(const float& delta)
{
    UpdateMousePositions();
    UpdateInput(delta);

    UpdateGui(delta);
}

void ScoreState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : buttons_)
    {
        it.second->Render(target);
    }
}

void ScoreState::Render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = window_;
    }
    
    target->draw(background_);

    RenderButtons(*target);

    target->draw(text_);
}

void ScoreState::ReadScoresFile()
{
    std::ifstream ifs("config/scores.ini");
    if (ifs.is_open())
    {
        std::string name  = "";
        int         score = 0;
        while (ifs >> name >> score)
        {
            scores_.insert(std::pair<std::string, int>(name, score));
        }
    }
    ifs.close();
}
