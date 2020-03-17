#include "Asteroid.h"

const float Asteroid::speed[3] = { 0.03f, 0.05f, 0.07f };

Asteroid::Asteroid(int level) :is_alive(true), level(level)
{
	int angle = rand() % 360;
	direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
}

Asteroid::~Asteroid()
{

}

Asteroid::Asteroid(sf::Vector2f position, float angle, int level) :is_alive(true), level(level)
{

}

bool Asteroid::isAlive() 
{ 
	return is_alive; 
}

int Asteroid::getLevel() 
{ 
	return level; 
}

bool Asteroid::checkPoint(sf::Vector2f point) 
{
	float ax = getPosition().x;
	float ay = getPosition().y;

	float px = point.x;
	float py = point.y;

	float sqrDistance = ((ax - px) * (ax - px)) + ((ay - py) * (ay - py));

	return true;
}
void Asteroid::breakDown(){}
void Asteroid::update(float frametime){}
void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const{}
