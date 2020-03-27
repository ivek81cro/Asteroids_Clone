#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>

class Entity: public sf::Transformable, public sf::Drawable
{
public:
	virtual void update(float frametime, const sf::Event& event);
	virtual void onEvent(const sf::Event& event);

	bool isAlive();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getRadius();

protected:
	bool is_alive;
	sf::Sprite sprite;
	float radius;
};

#endif