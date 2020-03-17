#include "Bullet.h"
#include "Constants.h"

const float Bullet::lifetime = 400.0f;
const float Bullet::speed = 2.0f;
bool Bullet::init_done;
sf::Texture Bullet::tBullet;

Bullet::Bullet(sf::Vector2f position, float angle) :
	is_alive(true), remaning_life(lifetime),
	direction(cos(angle* DEGTORAD), sin(angle* DEGTORAD))
{
	if (!init_done)
		Init("images/bullet.png");
	
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
	if (!is_alive) return;	

	remaning_life -= frametime;
	if (remaning_life <= 0)
		is_alive = false;

	sBullet.setTexture(tBullet);
	sBullet.setTextureRect(sf::IntRect(0, 0, 14, 44));
	sBullet.setOrigin(27, 10);

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
