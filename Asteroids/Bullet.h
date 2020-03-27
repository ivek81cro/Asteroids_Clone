#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include "Entity.h"


class Bullet : public Entity
{
	static bool init_done;
	static const float lifetime;
	static const float speed;
	static sf::Texture tBullet;
	

public:
	Bullet(sf::Vector2f position, float angle);
	~Bullet();

	void kill();
	void update(float frametime);
	static bool Init(const std::string& ImageFile);

private:
	float remaning_life;
	sf::Vector2f direction;
};

#endif