#include "Entity.h"

Entity::Entity()
{
    shape_.setSize(sf::Vector2f(50.f, 50.f));
    shape_.setFillColor(sf::Color::White);
    movement_speed_ = 100.0f;
}

Entity::~Entity()
{
}

void Entity::Move(const float& delta, const float dir_x, const float dir_y)
{
    shape_.move(dir_x * movement_speed_ * delta, dir_y * movement_speed_ * delta);
}

void Entity::Update(const float& delta)
{
}

void Entity::Render(sf::RenderTarget* target)
{
    target->draw(shape_);
}
