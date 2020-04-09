#include "Entity.h"

Entity::Entity()
{
    InitVariables();
}

Entity::~Entity()
{
    delete movement_component_;
}

//Component functions
void Entity::SetTexture(sf::Texture& texture)
{
    sprite_.setTexture(texture);
}

void Entity::CreateMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
{
    movement_component_ = new MovementComponent(sprite_, max_velocity, acceleration, deceleration);
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

void Entity::Move(const float dir_x, const float dir_y, const float& delta)
{
    if (movement_component_)
    {
        movement_component_->Move(dir_x, dir_y, delta); //Sets velocity
    }
}

void Entity::Update(const float& delta)
{
    if (movement_component_)
        movement_component_->Update(delta);
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
