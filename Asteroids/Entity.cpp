#include "Entity.h"

//Constructors / Destrustors
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

void Entity::CreateMovementComponent(const float max_velocity, const float acceleration, const float deceleration,
                                     const float& angle)
{
    movement_component_ = new MovementComponent(sprite_, max_velocity, acceleration, deceleration, angle, name_);
}

//Functions
void Entity::SetPosition(const float x, const float y)
{
    sprite_.setPosition(x, y);
}

void Entity::SetTextureRect(const int x, const int y, const int height, const int width)
{
    sprite_.setTextureRect(sf::IntRect(x, y, width, height));
}

void Entity::SetRotation(const float r)
{
    sprite_.setRotation(r);
}

void Entity::SetOrigin(const sf::Vector2f origin)
{
    sprite_.setOrigin(origin);
}

void Entity::Move(const float dir_x, const float dir_y, const float& delta)
{
    if (movement_component_)
    {
        movement_component_->Move(dir_x, dir_y, delta); //Sets velocity
    }
}

bool Entity::IsAlive()
{
    return alive_;
}

void Entity::SetAlive(bool is_alive)
{
    alive_ = is_alive;
}

std::string Entity::GetName()
{
    return name_;
}

void Entity::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (movement_component_)
        movement_component_->Update(delta, window_size);
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
