#include "Entity.h"

Entity::Entity()
{
    InitVariables();
}

Entity::~Entity()
{
}

//Component functions
void Entity::SetTexture(sf::Texture& texture)
{
    sprite_.setTexture(texture);
}

void Entity::CreateMovementComponent(const float max_velocity)
{
    movement_component_ = new MovementComponent(sprite_, max_velocity);
}

//Functions

void Entity::SetPosition(const float x, const float y)
{
        sprite_.setPosition(x, y);
}

void Entity::SetTextureRect(const int x, const int y, const int height, const int width)
{
    sprite_.setTextureRect(sf::IntRect(x, y, height, width));
}

void Entity::Move(const float& delta, const float dir_x, const float dir_y)
{
    if (movement_component_)
    {
        movement_component_->Move(dir_x, dir_y, delta); //Sets velocity
    }
}

void Entity::Update(const float& delta)
{
}

void Entity::Render(sf::RenderTarget* target)
{
        target->draw(sprite_);
}

//Initializer functions
void Entity::InitVariables()
{
    movement_component_ = nullptr;
}
