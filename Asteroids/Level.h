#ifndef _LEVEL_H_
#define _LEVEL_H

#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h" 
#include <SFML/Graphics.hpp>
#include <list>

class Level
{
public:
	Level();
	~Level();

	void onEvent(const sf::Event& event);
	void update(float framerate, const sf::Event& event);
	void show(sf::RenderTarget& target);
	void start();

private:
	Ship ship;
	std::list<Bullet> bullets;
	std::list<Asteroid> asteroids;
};

#endif