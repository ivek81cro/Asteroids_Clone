#include "stdafx.h"
#include "ScoreState.h"

//Constructor / Destructor
ScoreState::ScoreState(StateData* state_data, const int& score)
        : State(state_data)
        , current_player_score_(score)
{
    InitFonts();
    InitKeybinds();
    ReadScoresFile();
    CompareScore();
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

//Init functions
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

    InitBackground(vm);
    InitButtons(vm);
    InitText(vm);
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

void ScoreState::InitBackground(const sf::VideoMode& vm)
{
    //Backround
    background_.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (!textures_[ "BACKGROUND_TEXTURE" ].loadFromFile("Resources/Images/background.jpg"))
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_TEXTURE";
    }

    background_.setTexture(&textures_[ "BACKGROUND_TEXTURE" ]);
}

void ScoreState::InitButtons(const sf::VideoMode& vm)
{
    //Buttons
    float width  = gui::PercToPixelX(19.53f, vm);
    float height = gui::PercToPixelY(6.94f, vm);

    buttons_[ "BACK" ] = new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(90.19f, vm), width, height,
                                         &font_, "Back", gui::CalcFontSIze(vm, 60), sf::Color(255, 0, 0, 200),
                                         sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                                         sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0));
}

void ScoreState::InitText(const sf::VideoMode& vm)
{
    //Text
    name_.setFont(font_);
    name_.setPosition(sf::Vector2f(gui::PercToPixelX(30.82f, vm), gui::PercToPixelY(13.89f, vm)));
    name_.setCharacterSize(gui::CalcFontSIze(vm, 85));
    name_.setFillColor(sf::Color(250, 0, 0, 200));
    name_.setOutlineThickness(2);
    name_.setLineSpacing(1);

    score_.setFont(font_);
    score_.setPosition(sf::Vector2f(gui::PercToPixelX(60.82f, vm), gui::PercToPixelY(13.89f, vm)));
    score_.setCharacterSize(gui::CalcFontSIze(vm, 85));
    score_.setFillColor(sf::Color(250, 0, 0, 200));
    score_.setOutlineThickness(2);
    score_.setLineSpacing(1);

    std::string name_string  = "Player name:\n\n";
    std::string score_string = "Score:\n\n";

    for (auto& score : scores_)
    {
        name_string.append(score.second);
        name_string.append("\n");
        score_string.append(std::to_string(score.first));
        score_string.append("\n");
    }

    name_.setString(name_string);
    score_.setString(score_string);
}

//Functions
void ScoreState::ReadScoresFile()
{
    std::ifstream ifs("config/scores.ini");
    if (ifs.is_open())
    {
        std::string name  = "";
        int         score = 0;
        while (ifs >> name >> score)
        {
            scores_.insert(std::pair<int, std::string>(score, name));
        }
    }
    ifs.close();
}

void ScoreState::WriteScoresFile()
{
    std::ofstream ofs("config/scores.ini");

    if (ofs.is_open())
    {
        for (auto scores : scores_)
            ofs << scores.second << '\t' << scores.first << '\n';
    }

    ofs.close();
}

void ScoreState::CompareScore()
{
    for (auto itr = scores_.begin(); itr != scores_.end(); ++itr)
    {
        if (current_player_score_ >= (*itr).first )
        {
            scores_.erase(--scores_.end());
            scores_.insert(itr, std::pair<int, std::string>(current_player_score_, "New_Player"));
            break;
        }
    }
    WriteScoresFile();
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
    //Exit scoreboard
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

    target->draw(name_);
    target->draw(score_);
}
