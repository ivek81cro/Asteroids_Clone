#include "Level.h"

Level::Level()
{
	for (int i = 0; i < 5; i++) {
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
		bullets.push_back(Bullet (ship.getPosition(), ship.getRotation() - 90));
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
			//temp fix for double bullet creation
			if(start_bullets+1 != bullets.end())
				if (start_bullets->getPosition() == (start_bullets + 1)->getPosition())
					start_bullets->kill();
			//end
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

	std::vector<Asteroid> new_asteroids;
	start_asteroids = asteroids.begin();
	Collider cld;
	while (start_asteroids != asteroids.end()) {
		start_bullets = bullets.begin();
		while (start_bullets != bullets.end()) {
			if (!start_bullets->isAlive()) {
				++start_bullets;
				continue;
			}
			//work on bullet->asteroid collision
			if (cld.isCollide(*start_asteroids,*start_bullets)) {
				start_bullets->kill();
				start_asteroids->breakDown();

				if (start_asteroids->isAlive()) {
					sf::Vector2f position = start_asteroids->getPosition();
					float angle = rand() % 360;
					Asteroid a(position, angle, start_asteroids->getLevel());
					new_asteroids.push_back(a);
				}
				break;
			}
			++start_bullets;
		}
		if (cld.isCollide(*start_asteroids, ship))
		{
			ship.kill();
		}

		++start_asteroids;
	}
	asteroids.insert(asteroids.end(), new_asteroids.begin(), new_asteroids.end());
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

