#ifndef DROPDOWNBOX_H_
#define DROPDOWNBOX_H_

#include "Button.h"
#include "SFML/Graphics.hpp"

namespace gui
{
    class DropDownList
    {
      public:
        DropDownList(float x, float y, float width,float height, sf::Font& font, std::string list[], unsigned num_of_elements,
                     unsigned default_index = 0);
        virtual ~DropDownList();

        //Accessor
        const unsigned short& GetActiveElementId() const; 

        //Functions
        const bool GetKeytime();
        void       UpdateKeytime(const float& delta);
        void       Update(const sf::Vector2f& mouse_pos, const float& delta);
        void       Render(sf::RenderTarget& target);

      private:
        sf::Font&            font_;
        Button*              active_element_;
        std::vector<Button*> list_;

        float keytime_;
        float keytime_max_;
        bool  show_list_;
    };
} // namespace gui

#endif // !DROPDOWNBOX_H_
