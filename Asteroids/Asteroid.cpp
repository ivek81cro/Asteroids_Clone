#include "Asteroid.h"

const float Asteroid::speed[3] = { 0.03f, 0.06f, 0.09f };
bool Asteroid::init_done;
sf::Texture Asteroid::tAsteroid;

Asteroid::Asteroid(int level) :is_alive(true), level(level), ran(0), tick(0), radius(ASTEROID_RADIUS)
{
	int angle = rand() % 360;
	direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));

	if (!init_done)
		Init(ASTEROID_TEXTURE);

	setPosition(rand() % W_WIDTH, rand() % W_HEIGHT);
	setRotation(rand() % 360);
	sAsteroid.setTexture(tAsteroid);
	sAsteroid.setTextureRect(sf::IntRect(0 + ran, 6, 64, 64));
	//color added for testing
	sAsteroid.setColor(sf::Color(255, 255, 0));
	sAsteroid.setOrigin(32, 32);
}

Asteroid::~Asteroid()
{

}

Asteroid::Asteroid(sf::Vector2f position, float angle, int level) 
	:is_alive(true), level(level), ran(64), tick(0), radius(ASTEROID_RADIUS)
{
	direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
	setPosition(position);
	sAsteroid.setTexture(tAsteroid);
	sAsteroid.setTextureRect(sf::IntRect(0 + ran, 6, 64, 64));
	sAsteroid.setOrigin(32, 32);
	setScale(level == 2 ? 
		getScale() * ASTEROID_RESCALE_RADIUS_FACTOR * ASTEROID_RESCALE_RADIUS_FACTOR : 
		getScale() * ASTEROID_RESCALE_RADIUS_FACTOR);
	level == 2 ?
		radius *= ASTEROID_RESCALE_RADIUS_FACTOR * ASTEROID_RESCALE_RADIUS_FACTOR : 
		radius *= ASTEROID_RESCALE_RADIUS_FACTOR;
}

bool Asteroid::Init(const std::string& ImageFile)
{
	init_done = true;
	return tAsteroid.loadFromFile(ImageFile);
}

bool Asteroid::isAlive() 
{ 
	return is_alive; 
}

int Asteroid::getLevel() 
{ 
	return level; 
}

bool Asteroid::checkPoint(sf::Vector2f point, float radiusOther) {

	float ax = getPosition().x;
	float ay = getPosition().y;

	float px = point.x;
	float py = point.y;

	float sqrDistance = sqrt(((ax - px) * (ax - px)) + ((ay - py) * (ay - py)));
	float sqrRadius = radius + radiusOther;

 	return (sqrDistance <= sqrRadius);
}

void Asteroid::breakDown()
{
	level++;

	if (level > 2) {
		is_alive = false;
		return;
	}

	setScale(getScale() * ASTEROID_RESCALE_RADIUS_FACTOR);
	radius *= 0.75f;
	int angle = rand() % 360;
	direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
}

void Asteroid::update(float frametime)
{
	if (!is_alive) return;

	if (ran >= 1024) {
		ran = 0;
		tick = 0;
	}
	sAsteroid.setTextureRect(sf::IntRect(0 + ran, 6, 64, 64));
	
	if (tick % 4 == 0)
		ran += 64;
	++tick;

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
