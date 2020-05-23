#ifndef DROPDOWNBOX_H_
#define DROPDOWNBOX_H_

#include "Button.h"

namespace gui
{
    class DropDownList
    {
      public:
        DropDownList(float x, float y, float width, float height, sf::Font& font, sf::VideoMode vm, std::string list[],
                     unsigned num_of_elements, unsigned default_index, ButtonSettings* btn_settings);
        virtual ~DropDownList();

        //Accessor
        const unsigned short& GetActiveElementId();

        //Functions
        const bool GetKeytime();
        void       UpdateKeytime(const float& delta);
        void       Update(const sf::Vector2f& mouse_pos, const float& delta);
        void       Render(sf::RenderTarget& target);

        const bool& GetToggle();
        const bool& IsActive();
        const std::string GetActiveElementText() const;

      private:
        sf::Font&                            font_;
        std::unique_ptr<Button>              active_element_;
        std::vector<std::unique_ptr<Button>> list_;
        sf::VideoMode                        vm_;

        float keytime_;
        float keytime_max_;
        bool  show_list_;
        bool  toggle_;
    };
} // namespace gui

#endif // !DROPDOWNBOX_H_
