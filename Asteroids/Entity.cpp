#include "Entity.h"

bool Entity::isAlive()
{
    return is_alive;
}

float Entity::getRadius()
{
    return radius;
}

int Entity::getId()
{
    return id;
}

sf::Sprite& Entity::getSprite()
{
    return sprite;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= sprite.getTransform();
    target.draw(sprite, states);
}

void Entity::update(sf::Time& elapsedTime, const sf::Event& event)
{
}

void Entity::onEvent(const sf::Event& event)
{
}
