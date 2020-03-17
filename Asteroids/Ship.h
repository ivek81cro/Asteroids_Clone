#ifndef _SHIP_H_
#define _SHIP_H_

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Constants.h"
#include "Bullet.h"

class Ship : public sf::Drawable, public sf::Transformable
{
	static const float acceleration;
	static const float max_speed;
	static const float rotation_speed;

public:
	Ship();
	~Ship();

	void reset();
	void update(float frametime, const sf::Event& event);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void onEvent(const sf::Event& event);


private:
	sf::Vector2f speed;
	sf::Texture tShip;
	sf::Sprite sShip;
	int x_move;
	int y_move;
};

#endif
