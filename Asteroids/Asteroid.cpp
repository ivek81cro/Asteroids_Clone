#include "Asteroid.h"

const float Asteroid::speed[3] = { 0.03f, 0.05f, 0.07f };
bool Asteroid::init_done;
sf::Texture Asteroid::tAsteroid;

Asteroid::Asteroid(int level) :is_alive(true), level(level), ran(0)
{
	int angle = rand() % 360;
	direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));

	if (!init_done)
		Init("images/rock.png");

	setPosition(rand() % W_WIDTH, rand() % W_HEIGHT);
	setRotation(rand() % 360);
}

Asteroid::~Asteroid()
{

}

Asteroid::Asteroid(sf::Vector2f position, float angle, int level) :is_alive(true), level(level),ran(0)
{
	direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
	setPosition(position);
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

void Asteroid::update(float frametime)
{
	if (!is_alive) return;

	if (ran >= 1024)
		ran = 0;
	sAsteroid.setTexture(tAsteroid);
	sAsteroid.setTextureRect(sf::IntRect(0+ran, 6, 65, 64));
	sAsteroid.setOrigin(15, 25);

	ran += 64;

	sf::Vector2f distance = direction * speed[level] * frametime;
	move(distance);

	sf::Vector2f position = getPosition();

	if (position.x > W_WIDTH)
		position.x = 0;
	if (position.x < 0)
		position.x = W_WIDTH;

	if (position.y > W_HEIGHT)
		position.y = 0;
	if (position.y < 0)
		position.y = W_HEIGHT;

	setPosition(position);
}
void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sAsteroid, states);

}
