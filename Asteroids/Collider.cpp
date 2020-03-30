#include "Collider.h"

bool Collider::IsColide(Entity& obj1, Entity& obj2)
{

    float ax = obj1.GetSprite().getPosition().x;
    float ay = obj1.GetSprite().getPosition().y;

    float px = obj2.GetSprite().getPosition().x;
    float py = obj2.GetSprite().getPosition().y;

    float sqrDistance = sqrt((ax - px) * (ax - px) + (ay - py) * (ay - py));
    float sqrRadius   = obj1.GetRadius() + obj2.GetRadius();

    return (sqrDistance <= sqrRadius);
}
