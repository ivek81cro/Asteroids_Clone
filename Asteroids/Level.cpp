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

void Level::OnEvent(const sf::Event& event)
{
    mShip.OnEvent(event);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Bullet bullet(mShip.GetSprite().getPosition(), mShip.GetSprite().getRotation() - 90);
        mBullets.push_back(bullet);
    }
}

void Level::Update(sf::Time& elapsedTime, const sf::Event& event)
{
    mShip.Update(elapsedTime, event);

    std::vector<Bullet>::iterator start_bullets = mBullets.begin();
    while (start_bullets != mBullets.end())
    {
        if (start_bullets->IsAlive())
        {
            //temp fix for double bullet creation
            if (start_bullets + 1 != mBullets.end())
                if (start_bullets->GetSprite().getPosition() == (start_bullets + 1)->GetSprite().getPosition())
                    start_bullets->Kill();
            //end
            start_bullets->Update(elapsedTime);
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
        if (start_asteroids->IsAlive())
        {
            start_asteroids->Update(elapsedTime);
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
        if (cld.IsColide(*start_asteroids, mShip))
        {
            if (mShip.GetRadius() != 0)
                mShip.Kill();
        }

        ++start_asteroids;
    }
    mAsteroids.insert(mAsteroids.end(), new_asteroids.begin(), new_asteroids.end());
}

void Level::Show(sf::RenderTarget& target)
{
    target.draw(mShip.GetSprite());

    for (std::vector<Bullet>::iterator it = mBullets.begin(); it != mBullets.end(); ++it)
    {
        target.draw(it->GetSprite());
    }

    for (std::vector<Asteroid>::iterator it = mAsteroids.begin(); it != mAsteroids.end(); ++it)
    {
        target.draw(it->GetSprite());
    }
}

void Level::Start()
{
}
