#include "Asteroid.h"

const float Asteroid::speed[ 3 ] = {0.03f, 0.06f, 0.09f};
bool        Asteroid::init_done;
sf::Texture Asteroid::tAsteroid;

Asteroid::Asteroid(int level)
        : level(level)
{
    int angle = rand() % 360;
    direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));

    if (!init_done)
        Init(ASTEROID_TEXTURE);

    sprite.setPosition(rand() % W_WIDTH, rand() % W_HEIGHT);
    sprite.setRotation(rand() % 360);
    sprite.setTexture(tAsteroid);
    sprite.setTextureRect(sf::IntRect(0 + mMoveRect, 6, 64, 64));
    //color added for testing
    sprite.setColor(sf::Color(255, 255, 0));
    sprite.setOrigin(32, 32);
    is_alive = true;
    radius   = ASTEROID_RADIUS;
    id       = ID_ASTEROID;
}

Asteroid::~Asteroid()
{
}

Asteroid::Asteroid(sf::Vector2f position, float angle, int level)
        : level(level)
{
    direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
    sprite.setPosition(position);
    sprite.setTexture(tAsteroid);
    sprite.setTextureRect(sf::IntRect(0 + mMoveRect, 6, 64, 64));
    sprite.setOrigin(32, 32);
    radius   = ASTEROID_RADIUS;
    is_alive = true;
    id       = ID_ASTEROID;
    mMoveRect      = 64;
    sprite.setScale(level == 2 ? sprite.getScale() * ASTEROID_RESCALE_RADIUS_FACTOR * ASTEROID_RESCALE_RADIUS_FACTOR
                               : sprite.getScale() * ASTEROID_RESCALE_RADIUS_FACTOR);
    level == 2 ? radius *= ASTEROID_RESCALE_RADIUS_FACTOR* ASTEROID_RESCALE_RADIUS_FACTOR
               : radius *= ASTEROID_RESCALE_RADIUS_FACTOR;
}

bool Asteroid::Init(const std::string& ImageFile)
{
    init_done = true;
    return tAsteroid.loadFromFile(ImageFile);
}

int Asteroid::getLevel()
{
    return level;
}

void Asteroid::breakDown()
{
    level++;

    if (level > 2)
    {
        is_alive = false;
        return;
    }

    sprite.setScale(sprite.getScale() * ASTEROID_RESCALE_RADIUS_FACTOR);
    radius *= 0.75f;
    int angle = rand() % 360;
    direction = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
}

void Asteroid::update(float& elapsedTime)
{
    if (!is_alive)
        return;

    if (mMoveRect >= 1024)
    {
        mMoveRect  = 0;
        mElapsedTime = 0;
    }
    sprite.setTextureRect(sf::IntRect(0 + mMoveRect, 6, 64, 64));

    float frametime = .125f / 60.0f * 1000.0f;
    if (mElapsedTime >= frametime)
    {
        mMoveRect += 64;
        mElapsedTime = 0;
    }
    ++mElapsedTime;

    sf::Vector2f distance = direction * speed[ level ] * elapsedTime;
    sprite.move(distance);

    sf::Vector2f position = sprite.getPosition();

    if (position.x > W_WIDTH)
        position.x = 0;
    if (position.x < 0)
        position.x = W_WIDTH;

    if (position.y > W_HEIGHT)
        position.y = 0;
    if (position.y < 0)
        position.y = W_HEIGHT;

    sprite.setPosition(position);
}
