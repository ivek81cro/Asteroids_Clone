#include "DropDownList.h"

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[],
                                unsigned num_of_elements, unsigned default_index)
        : font_(font)
        , show_list_(false)
        , keytime_max_(1.f)
        , keytime_(0.f)
{

    active_element_ = new Button(x, y, width, height, &font_, list[ default_index ], 16, sf::Color(250, 0, 0, 255),
                                 sf::Color(250, 90, 90, 200), sf::Color(250, 200, 200, 100), sf::Color(0, 0, 0, 200),
                                 sf::Color(0, 0, 0, 200), sf::Color(20, 20, 20, 200));

    for (size_t i = 0; i < num_of_elements; i++)
    {
        list_.push_back(new Button(x, (y + (i + 1) * height), width, height, &font_, list[ i ], 16,
                                   sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 50),
                                   sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 200), i));
    }
}

gui::DropDownList::~DropDownList()
{
    delete active_element_;

    for (auto& i : list_)
        delete i;

    /*for (size_t i = 0; i < list_.size(); i++)
    {
        delete list_[ i ];
    }*/
}

//Accessor
const unsigned short& gui::DropDownList::GetActiveElementId() const
{
    return active_element_->GetId();
}

const bool gui::DropDownList::GetKeytime()
{
    if (keytime_ >= keytime_max_)
    {
        keytime_ = 0.f;
        return true;
    }
    return false;
}

//Functions
void gui::DropDownList::UpdateKeytime(const float& delta)
{
    if (keytime_ < keytime_max_)
        keytime_ += 5.f * delta;
}

void gui::DropDownList::Update(const sf::Vector2f& mouse_pos, const float& delta)
{
    UpdateKeytime(delta);

    active_element_->Update(mouse_pos);

    if (active_element_->IsPressed() && GetKeytime())
    {
        if (show_list_)
            show_list_ = false;
        else
            show_list_ = true;
    }

    if (show_list_)
    {
        for (auto& i : list_)
        {
            i->Update(mouse_pos);

            if (i->IsPressed() && GetKeytime())
            {
                show_list_ = false;
                active_element_->SetText(i->GetText());
                active_element_->SetId(i->GetId());
            }
        }
    }
}

void gui::DropDownList::Render(sf::RenderTarget& target)
{
    active_element_->Render(target);

    if (show_list_)
    {
        for (auto& i : list_)
        {
            i->Render(target);
        }
    }
}
