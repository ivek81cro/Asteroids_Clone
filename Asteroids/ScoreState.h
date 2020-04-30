#ifndef SCORESTATE_H_
#define SCORESTATE_H_

#include "Button.h"
#include "State.h"

class ScoreState : public State
{
  public:
    ScoreState(StateData* state_data, const int& score);
    virtual ~ScoreState();

    //Functions
    void UpdateInput(const float& delta);
    void UpdateGui(const float& delta);
    void Update(const float& delta);
    void RenderButtons(sf::RenderTarget& target);
    void Render(sf::RenderTarget* target = nullptr);

    void ReadScoresFile();
    bool WriteScoresFile();
    void CompareScore();

  private:
    //Variables
    sf::RectangleShape background_;
    sf::Font           font_;

    std::map<std::string, gui::Button*> buttons_;
    sf::Text                            name_;
    sf::Text                            score_;

    std::multimap<int, std::string, std::greater<int>> scores_;
    std::vector<sf::VideoMode> v_modes_;

    void InitFonts();
    void InitGui();
    void InitKeybinds();
};
#endif
