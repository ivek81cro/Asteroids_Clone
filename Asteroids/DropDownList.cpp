#include "stdafx.h"
#include "DropDownList.h"

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, sf::VideoMode vm, std::string list[],
                                unsigned num_of_elements, unsigned default_index, ButtonSettings* btn_settings)
        : font_(font)
        , show_list_(false)
        , keytime_max_(1.f)
        , keytime_(0.f)
        , toggle_(false)
        , vm_(vm)
{
    //Add  buttons to dropdown list and set active one
    active_element_ = std::unique_ptr<Button>(
        new Button(x, y, width, height, &font_, list[ default_index ], CalcFontSize(vm_, 140),
                   btn_settings->btn_ddl_txt_idle_, btn_settings->btn_ddl_txt_hover_, btn_settings->btn_ddl_txt_active_,
                   btn_settings->btn_ddl_bg_idle_, btn_settings->btn_ddl_bg_hover_, btn_settings->btn_ddl_bg_active_));

    for (size_t i = 0; i < num_of_elements; i++)
    {
        list_.push_back(std::unique_ptr<Button> (
            new Button( x, (y + (i + 1) * height * 0.8f), width, height * 0.8f, &font_, list[ i ], CalcFontSize(vm_, 140),
            btn_settings->btn_ddl_txt_idle_, btn_settings->btn_ddl_txt_hover_, btn_settings->btn_ddl_txt_active_,
            btn_settings->btn_ddl_bg_idle_, btn_settings->btn_ddl_bg_hover_, btn_settings->btn_ddl_bg_active_, i)));
    }
}

gui::DropDownList::~DropDownList()
{
    
}

//Accessor
const unsigned short& gui::DropDownList::GetActiveElementId()
{
    return active_element_->GetId();
}

const std::string gui::DropDownList::GetActiveElementText() const
{
    return active_element_->GetText();
}

/**
    Limits repeatnig if holding button
*/
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

/**
    Update ddl, expand or collapse
*/
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
                
                toggle_ = true;
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

const bool& gui::DropDownList::GetToggle()
{
    return toggle_;
}

const bool& gui::DropDownList::IsActive()
{
    return show_list_;
}
