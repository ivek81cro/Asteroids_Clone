#include "Entity.h"

bool Entity::isAlive()
{
	return is_alive;
}

float Entity::getRadius()
{
	return radius;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Entity::update(float frametime, const sf::Event& event) {}

void Entity::onEvent(const sf::Event& event) {}
