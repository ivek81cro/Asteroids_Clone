#ifndef BUTTON_H_
#define BUTTON_H_

enum button_states
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

enum class Buttons
{
    Apply,
    Back,
    Quit,
    Game_state,
    Settings_state,
    Score_state,
    Exit_state,
    Wasd,
    Arrows
};

namespace gui
{
    const float    PercToPixelX(const float perc, const sf::VideoMode& vm);
    const float    PercToPixelY(const float perc, const sf::VideoMode& vm);
    const unsigned CalcFontSize(const sf::VideoMode& vm, const unsigned modifier);

    class Button
    {
      public:
        Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color,
               sf::Color hover_color, sf::Color active_color, short unsigned id = 0);
        virtual ~Button();

        //Accessors
        const bool            IsPressed() const;
        const std::string     GetText() const;
        const short unsigned& GetId();

        //Modifiers
        void SetText(const std::string text);
        void SetId(const short unsigned id);

        //Functions
        void Update(const sf::Vector2f& mouse_pos);
        void Render(sf::RenderTarget& target);

      private:
        short unsigned button_state_;
        short unsigned id_;

        sf::RectangleShape shape_;
        sf::Font*          font_;
        sf::Text           text_;

        sf::Color text_idle_color_;
        sf::Color text_hover_color_;
        sf::Color text_active_color_;

        sf::Color idle_color_;
        sf::Color hover_color_;
        sf::Color active_color_;
    };
} // namespace gui

#endif // !BUTTON_H_
