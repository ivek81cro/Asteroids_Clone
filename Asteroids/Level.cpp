#include "Level.h"

Level::Level()
{
    for (int i = 0; i < 5; i++)
    {
        Asteroid a(0);
        mAsteroids.push_back(a);
    }
}

Level::~Level()
{
}

void Level::onEvent(const sf::Event& event)
{
    mShip.onEvent(event);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Bullet bullet(mShip.getSprite().getPosition(), mShip.getSprite().getRotation() - 90);
        mBullets.push_back(bullet);
    }
}

void Level::update(sf::Time& elapsedTime, const sf::Event& event)
{
    mShip.update(elapsedTime, event);

    std::vector<Bullet>::iterator start_bullets = mBullets.begin();
    while (start_bullets != mBullets.end())
    {
        if (start_bullets->isAlive())
        {
            //temp fix for double bullet creation
            if (start_bullets + 1 != mBullets.end())
                if (start_bullets->getSprite().getPosition() == (start_bullets + 1)->getSprite().getPosition())
                    start_bullets->kill();
            //end
            start_bullets->update(elapsedTime);
            ++start_bullets;
        }
        else
        {
            start_bullets = mBullets.erase(start_bullets);
        }
    }

    std::vector<Asteroid>::iterator start_asteroids = mAsteroids.begin();
    while (start_asteroids != mAsteroids.end())
    {
        if (start_asteroids->isAlive())
        {
            start_asteroids->update(elapsedTime);
            ++start_asteroids;
        }
        else
            start_asteroids = mAsteroids.erase(start_asteroids);
    }

    std::vector<Asteroid> new_asteroids;
    start_asteroids = mAsteroids.begin();
    Collider cld;
    while (start_asteroids != mAsteroids.end())
    {
        start_bullets = mBullets.begin();
        while (start_bullets != mBullets.end())
        {
            if (!start_bullets->isAlive())
            {
                ++start_bullets;
                continue;
            }

            if (cld.isCollide(*start_asteroids, *start_bullets))
            {
                start_bullets->kill();
                start_asteroids->breakDown();

                if (start_asteroids->isAlive())
                {
                    sf::Vector2f position = start_asteroids->getSprite().getPosition();
                    float        angle    = rand() % 360;
                    Asteroid     a(position, angle, start_asteroids->getLevel());
                    new_asteroids.push_back(a);
                }
                break;
            }
            ++start_bullets;
        }
        if (cld.isCollide(*start_asteroids, mShip))
        {
            if (mShip.getRadius() != 0)
                mShip.kill();
        }

        ++start_asteroids;
    }
    mAsteroids.insert(mAsteroids.end(), new_asteroids.begin(), new_asteroids.end());
}

void Level::show(sf::RenderTarget& target)
{
    target.draw(mShip.getSprite());

    for (std::vector<Bullet>::iterator it = mBullets.begin(); it != mBullets.end(); ++it)
    {
        target.draw(it->getSprite());
    }

    for (std::vector<Asteroid>::iterator it = mAsteroids.begin(); it != mAsteroids.end(); ++it)
    {
        target.draw(it->getSprite());
    }
}

void Level::start()
{
}
