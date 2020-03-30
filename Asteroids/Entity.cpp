#include "Entity.h"

Entity::Entity(int moveRect, float elapsedTime, int id, float radius, bool isAlive)
        : mElapsedTime(elapsedTime)
        , mMoveRect(moveRect)
        , mId(id)
        , mRadius(radius)
        , mAlive(isAlive)
{
}

bool Entity::IsAlive()
{
    return mAlive;
}

float Entity::GetRadius()
{
    return mRadius;
}

int Entity::GetId()
{
    return mId;
}

sf::Sprite& Entity::GetSprite()
{
    return mSprite;
}

void Entity::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= mSprite.getTransform();
    target.draw(mSprite, states);
}

void Entity::Update(sf::Time& elapsedTime, const sf::Event& event)
{
}

void Entity::OnEvent(const sf::Event& event)
{
}
