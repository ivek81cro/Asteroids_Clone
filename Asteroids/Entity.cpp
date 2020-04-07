#include "Entity.h"

Entity::Entity()
{
    InitVariables();
}

Entity::~Entity()
{
    delete sprite_;
}

//Component functions
void Entity::CreateSprite(sf::Texture* texture)
{
    texture_ = texture;
    sprite_->setTexture(*texture_);
}

//Functions
void Entity::Move(const float& delta, const float dir_x, const float dir_y)
{
    if (sprite_)
    {
        sprite_->move(dir_x * movement_speed_ * delta, dir_y * movement_speed_ * delta);
    }
}

void Entity::Update(const float& delta)
{
}

void Entity::Render(sf::RenderTarget* target)
{
    target->draw(*sprite_);
}

//Initializer functions
void Entity::InitVariables()
{
    texture_        = nullptr;
    sprite_         = nullptr;
    movement_speed_ = 100.f;
}
