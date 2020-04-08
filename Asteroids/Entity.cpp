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
    sprite_  = new sf::Sprite(*texture_);
}

void Entity::CreateMovementComponent(const float max_velocity)
{
    movement_component_ = new MovementComponent(max_velocity);
}

//Functions

void Entity::SetPosition(const float x, const float y)
{
    if (sprite_)
    {
        sprite_->setPosition(x, y);
    }
}

void Entity::SetTextureRect(const int x, const int y, const int height, const int width)
{
    if (sprite_)
    {
        sprite_->setTextureRect(sf::IntRect(x, y, height, width));
    }
}

void Entity::Move(const float& delta, const float dir_x, const float dir_y)
{
    if (sprite_ && movement_component_)
    {
        movement_component_->Move(dir_x, dir_y); //Sets velocity
        sprite_->move(movement_component_->GetVelocity() * delta); //Uses velocity
    }
}

void Entity::Update(const float& delta)
{
}

void Entity::Render(sf::RenderTarget* target)
{
    if (sprite_)
    {
        target->draw(*sprite_);
    }
}

//Initializer functions
void Entity::InitVariables()
{
    texture_            = nullptr;
    sprite_             = nullptr;
    movement_component_ = nullptr;
}
