#ifndef SCORESTATE_H_
#define SCORESTATE_H_

#include "Button.h"
#include "State.h"

class ScoreState : public State
{
  public:
    ScoreState(StateData* state_data, const int& score = 0, bool writable = false);
    virtual ~ScoreState();

    //Functions
    void ReadScoresFile();
    void WriteScoresFile();
    void CompareScore();
    void RefreshScores();

    void UpdateInput(const float& delta);
    void UpdateGui(const float& delta);
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);


  private:
    //Variables
    sf::RectangleShape background_;
    sf::Font           font_;

    std::map<Buttons, std::unique_ptr<gui::Button>> buttons_;
    sf::Text                                            name_;
    sf::Text                                            score_;
    sf::Text                                            player_name_;
    sf::Text                                            name_text_;
    sf::RectangleShape                                  name_rect_;

    std::string str_name_;
    sf::Clock   elapsed_coldown_;
    sf::Clock   key_clock_;
    sf::Time    key_cooldown_;

    bool     writable_;
    bool     score_entered_;
    int      current_player_score_;
    unsigned max_name_length_;

    std::multimap<int, std::string, std::greater<int>> scores_;
    std::vector<sf::VideoMode>                         v_modes_;

    //Init functions
    void InitFonts();
    void InitGui();
    void InitKeybinds();
    void InitBackground(const sf::VideoMode& vm);
    void InitButtons(const sf::VideoMode& vm);
    void InitText(const sf::VideoMode& vm);
};
#endif
