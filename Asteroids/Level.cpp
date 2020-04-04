#include "Level.h"

Level::Level()
{
    for (int i = 0; i < 5; i++)
    {
        Asteroid a(0);
        asteroids.push_back(a);
    }
}

Level::~Level()
{
}

void Level::onEvent(const sf::Event& event)
{
    ship.OnEvent(event);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Bullet bullet(ship.GetSprite().getPosition(), ship.GetSprite().getRotation() - 90);
        bullets.push_back(bullet);
    }
}

void Level::update(sf::Time& elapsedTime, const sf::Event& event)
{
    ship.Update(elapsedTime, event);

    std::vector<Bullet>::iterator start_bullets = bullets.begin();
    while (start_bullets != bullets.end())
    {
        if (start_bullets->IsAlive())
        {
            //temp fix for double bullet creation
            if (start_bullets + 1 != bullets.end())
                if (start_bullets->GetSprite().getPosition() == (start_bullets + 1)->GetSprite().getPosition())
                    start_bullets->Kill();
            //end
            start_bullets->Update(elapsedTime);
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
        if (start_asteroids->IsAlive())
        {
            start_asteroids->Update(elapsedTime);
            ++start_asteroids;
        }
        else
            start_asteroids = asteroids.erase(start_asteroids);
    }

    std::vector<Asteroid> new_asteroids;
    start_asteroids = asteroids.begin();
    Collider cld;
    while (start_asteroids != asteroids.end())
    {
        start_bullets = bullets.begin();
        while (start_bullets != bullets.end())
        {
            if (!start_bullets->IsAlive())
            {
                ++start_bullets;
                continue;
            }

            if (cld.IsColide(*start_asteroids, *start_bullets))
            {
                start_bullets->Kill();
                start_asteroids->BreakDown();

                if (start_asteroids->IsAlive())
                {
                    sf::Vector2f position = start_asteroids->GetSprite().getPosition();
                    float        angle    = rand() % 360;
                    Asteroid     a(position, angle, start_asteroids->GetLevel());
                    new_asteroids.push_back(a);
                }
                break;
            }
            ++start_bullets;
        }
        if (cld.IsColide(*start_asteroids, ship))
        {
            if (ship.GetRadius() != 0)
                ship.Kill();
        }

        ++start_asteroids;
    }
    asteroids.insert(asteroids.end(), new_asteroids.begin(), new_asteroids.end());
}

void Level::show(sf::RenderTarget& target)
{
    target.draw(ship.GetSprite());

    for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
    {
        target.draw(it->GetSprite());
    }

    for (std::vector<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
    {
        target.draw(it->GetSprite());
    }
}

void Level::start()
{
}
