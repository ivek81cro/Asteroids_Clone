#include "Bullet.h"
#include "Constants.h"

const float Bullet::lifetime = 1.0f;
const float Bullet::speed = 0.09f;

Bullet::Bullet(sf::Vector2f position, float angle) :
	is_alive(true), remaning_life(lifetime),
	direction(cos(angle* DEGTORAD), sin(angle* DEGTORAD))
{
	setPosition(position);
	setRotation(angle + 90);
	setScale(0.25f, 0.25f);
}

Bullet::~Bullet()
{

}

bool Bullet::isAlive()
{
	return is_alive;
}

void Bullet::update(float frametime)
{
	tBullet.loadFromFile("images/fire_blue.png");
	sBullet.setTexture(tBullet);
	sBullet.setTextureRect(sf::IntRect(5, 0, 20, 55));
	sBullet.setOrigin(27, 10);
	if (!is_alive) return;

	remaning_life = frametime;
	if (remaning_life <= 0)
		is_alive = false;

	sf::Vector2f distance = direction * speed * frametime;

	move(distance);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sBullet, states);
}

void Bullet::kill()
{
	is_alive = false;
}
