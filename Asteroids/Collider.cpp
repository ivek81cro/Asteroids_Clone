#include "Collider.h"

bool Collider::isCollide(Entity obj1, Entity obj2) {

	float ax = obj1.getPosition().x;
	float ay = obj1.getPosition().y;

	float px = obj2.getPosition().x;
	float py = obj2.getPosition().y;

	float sqrDistance = sqrt((ax - px) * (ax - px) + (ay - py) * (ay - py));
	float sqrRadius = obj1.getRadius() + obj2.getRadius();

	return (sqrDistance <= sqrRadius);
}