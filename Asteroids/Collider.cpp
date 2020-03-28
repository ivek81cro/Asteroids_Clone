#include "Collider.h"

bool Collider::isCollide(Entity& obj1, Entity& obj2)
{

    float ax = obj1.getSprite().getPosition().x;
    float ay = obj1.getSprite().getPosition().y;

    float px = obj2.getSprite().getPosition().x;
    float py = obj2.getSprite().getPosition().y;

    float sqrDistance = sqrt((ax - px) * (ax - px) + (ay - py) * (ay - py));
    float sqrRadius   = obj1.getRadius() + obj2.getRadius();

    return (sqrDistance <= sqrRadius);
}
