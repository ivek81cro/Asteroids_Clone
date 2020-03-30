#include "Entity.h"

Entity::Entity(int moveRect, float elapsedTime, int id, float radius, bool isAlive)
        : mElapsedTime(elapsedTime)
        , mMoveRect(moveRect)
        , mId(id)
        , mRadius(radius)
        , mAlive(isAlive)
{
}

bool Entity::isAlive()
{
    return mAlive;
}

float Entity::getRadius()
{
    return mRadius;
}

int Entity::getId()
{
    return mId;
}

sf::Sprite& Entity::getSprite()
{
    return mSprite;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= mSprite.getTransform();
    target.draw(mSprite, states);
}

void Entity::update(sf::Time& elapsedTime, const sf::Event& event)
{
}

void Entity::onEvent(const sf::Event& event)
{
}
