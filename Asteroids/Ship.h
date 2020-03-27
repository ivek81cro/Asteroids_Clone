#ifndef _SHIP_H_
#define _SHIP_H_

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Constants.h"
#include "Bullet.h"
#include "Entity.h"

class Ship : public Entity
{
	static const float acceleration;
	static const float max_speed;
	static const float rotation_speed;

public:
	Ship();
	~Ship();
	void reset();
	void update(float frametime, const sf::Event& event);
	void onEvent(const sf::Event& event);
	void shipExplode();
	void kill();
	void moveShip(float frametime, const sf::Event& event);
	sf::Vector2f checkPosition();

private:
	sf::Vector2f speed;
	sf::Texture tShip;
	int x_move;
	int y_move;
};

#endif

