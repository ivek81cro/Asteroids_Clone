#include "Level.h"

Level::Level()
{
	for (int i = 0; i < 10; i++) {
		Asteroid a(0);
		asteroids.push_back(a);
	}
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

	std::vector<Asteroid>::iterator start_asteroids = asteroids.begin();
	while (start_asteroids != asteroids.end()) 
	{
		if (start_asteroids->isAlive()) 
		{
			start_asteroids->update(frametime);
			++start_asteroids;
		}
		else
			start_asteroids = asteroids.erase(start_asteroids);
	}
}

void Level::show(sf::RenderTarget& target)
{
	target.draw(ship);

	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		target.draw(*it);
	}

	for (std::vector<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
	{
		target.draw(*it);
	}
}

void Level::start()
{

}
