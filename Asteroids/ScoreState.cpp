#include "stdafx.h"
#include "ScoreState.h"

//Constructor / Destructor
ScoreState::ScoreState(StateData* state_data, const int& score, bool writable)
        : State(state_data)
        , current_player_score_(score)
        , str_name_("")
        , max_name_length_(25)
        , score_entered_(false)
        , writable_(writable)
{
    InitFonts();
    InitKeybinds();
    ReadScoresFile();
    InitGui();
}

ScoreState::~ScoreState()
{
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

    buttons_[ "BACK" ] = std::unique_ptr<gui::Button>(
        new gui::Button(gui::PercToPixelX(40.23f, vm), gui::PercToPixelY(90.19f, vm), width, height,
                                         &font_, "Back", gui::CalcFontSize(vm, 60), sf::Color(255, 0, 0, 200),
                                         sf::Color(255, 102, 102, 250), sf::Color(204, 0, 0, 50),
                                         sf::Color(255, 0, 0, 0), sf::Color(255, 102, 102, 0), sf::Color(204, 0, 0, 0)));
}

void ScoreState::InitText(const sf::VideoMode& vm)
{
    //Text
    name_.setFont(font_);
    name_.setPosition(sf::Vector2f(gui::PercToPixelX(30.82f, vm), gui::PercToPixelY(15.89f, vm)));
    name_.setCharacterSize(gui::CalcFontSize(vm, 85));
    name_.setFillColor(sf::Color(250, 0, 0, 200));
    name_.setOutlineThickness(2);
    name_.setLineSpacing(1);

    score_.setFont(font_);
    score_.setPosition(sf::Vector2f(gui::PercToPixelX(60.82f, vm), gui::PercToPixelY(15.89f, vm)));
    score_.setCharacterSize(gui::CalcFontSize(vm, 85));
    score_.setFillColor(sf::Color(250, 0, 0, 200));
    score_.setOutlineThickness(2);
    score_.setLineSpacing(1);

    //TODO maybe extract to separate function
    name_text_.setFont(font_);
    name_text_.setPosition(sf::Vector2f(gui::PercToPixelX(10.f, vm), gui::PercToPixelY(5.f, vm)));
    name_text_.setCharacterSize(gui::CalcFontSize(vm, 85));
    name_text_.setFillColor(sf::Color(250, 0, 0, 200));
    name_text_.setOutlineThickness(2);
    std::string name_text = "Enter your name please: ";
    name_text_.setString(name_text);

    player_name_.setFont(font_);
    player_name_.setPosition(sf::Vector2f(gui::PercToPixelX(10.f, vm), gui::PercToPixelY(10.f, vm)));
    player_name_.setCharacterSize(gui::CalcFontSize(vm, 85));
    player_name_.setFillColor(sf::Color::Black);
    player_name_.setString(str_name_);

    name_rect_.setSize(sf::Vector2f(gui::PercToPixelX(20.f, vm), gui::PercToPixelY(4.3f, vm)));
    name_rect_.setPosition(sf::Vector2f(gui::PercToPixelX(10.f, vm), gui::PercToPixelY(10.2f, vm)));
    name_rect_.setFillColor(sf::Color::White);
    name_rect_.setOutlineThickness(2);
    name_rect_.setOutlineColor(sf::Color(250, 0, 0, 200));

    RefreshScores();
}

//Functions
void ScoreState::ReadScoresFile()
{
    std::ifstream ifs("Config/scores.ini");
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
    std::ofstream ofs("Config/scores.ini");

    if (ofs.is_open())
    {
        for (auto scores : scores_)
            ofs << scores.second << '\t' << scores.first << '\n';
        score_entered_ = true;
    }
    ofs.close();
}

void ScoreState::CompareScore()
{
    if (scores_.size() <= 10)
    {
        scores_.insert(std::pair<int, std::string>(current_player_score_, str_name_));
    }
    else
    {
        for (auto itr = scores_.begin(); itr != scores_.end(); ++itr)
        {
            if (current_player_score_ >= (*itr).first)
            {
                if (scores_.size() > 10)
                    scores_.erase(--scores_.end());
                scores_.insert(itr, std::pair<int, std::string>(current_player_score_, str_name_));
                break;
            }
        }
    }
    WriteScoresFile();
    RefreshScores();
}

void ScoreState::RefreshScores()
{
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

void ScoreState::UpdateInput(const float& delta)
{
    key_cooldown_ = key_clock_.getElapsedTime();
    if (state_data_->event_->type == sf::Event::TextEntered && key_cooldown_.asSeconds() > 0.10f && !score_entered_ && writable_)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace) && str_name_.size() > 0)
        {
            str_name_.erase(str_name_.size() - 1);
            player_name_.setString(str_name_);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
        {

            if (str_name_.length() > 1)
            {
                if (str_name_.front() != '\r')
                    CompareScore();
                str_name_.clear();
            }
        }
        if (state_data_->event_->text.unicode != 8 && str_name_.length() < max_name_length_)
        {
            if (state_data_->event_->text.unicode != '\r')
                str_name_ += (char)state_data_->event_->text.unicode;
            player_name_.setString(str_name_);
        }

        key_clock_.restart();
    }
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
    if (buttons_[ "BACK" ]->IsPressed() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
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
    target->draw(name_rect_);
    target->draw(name_text_);
    target->draw(player_name_);
}
