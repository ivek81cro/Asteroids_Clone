#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Asteroid : public sf::Drawable, public sf::Transformable
{
	static const float speed[3];

public:
	Asteroid(int level);
	Asteroid(sf::Vector2f position, float angle, int level);
	~Asteroid();

	bool isAlive();
	int getLevel();
	bool checkPoint(sf::Vector2f point);
	void breakDown();
	void update(float frametime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	int level;
	bool is_alive;
	sf::Vector2f direction;
	sf::Texture tAsteroid;
	sf::Sprite sAsteroid;
};

#endif