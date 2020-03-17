#include "Level.h"

Level::Level()
{

}

Level::~Level()
{

}

void Level::onEvent(const sf::Event& event)
{
	ship.onEvent(event);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Bullet bullet(ship.getPosition(), ship.getRotation() - 90);
		bullets.push_back(bullet);
	}
}

void Level::update(float frametime, const sf::Event& event)
{
	ship.update(frametime, event);

	std::vector<Bullet>::iterator start_bullets = bullets.begin();
	while (start_bullets != bullets.end())
	{
		if (start_bullets->isAlive())
		{
			start_bullets->update(frametime);
			++start_bullets;
		}
		else
		{
			start_bullets = bullets.erase(start_bullets);
		}
	}
}

void Level::show(sf::RenderTarget& target)
{
	target.draw(ship);

	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		target.draw(*it);
	}
}

void Level::start()
{

}
