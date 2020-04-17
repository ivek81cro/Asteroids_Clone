#ifndef DROPDOWNBOX_H_
#define DROPDOWNBOX_H_

#include "SFML/Graphics.hpp"
#include "Button.h"

namespace gui
{
    class DropDownList
    {
      public:
        DropDownList();
        virtual ~DropDownList();

        void Update(const sf::Vector2f& mouse_pos);
        void Render(sf::RenderTarget& target);

      private:
        sf::Font&                       font_;
        sf::RectangleShape              active_element_;
        std::vector<gui::Button*> list_;
    };
} // namespace gui

#endif // !DROPDOWNBOX_H_
