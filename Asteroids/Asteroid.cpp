#include "Asteroid.h"

const float Asteroid::speed[ 3 ] = {0.03f, 0.06f, 0.09f};
bool        Asteroid::init_done;
sf::Texture Asteroid::tAsteroid;

Asteroid::Asteroid(int level)
        : mLevel(level)
        , Entity(0, 0, ID_ASTEROID, ASTEROID_RADIUS, true)
{
    int angle = rand() % 360;
    mDirection = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));

    if (!init_done)
        Init(ASTEROID_TEXTURE);

    mSprite.setPosition(rand() % W_WIDTH, rand() % W_HEIGHT);
    mSprite.setRotation(rand() % 360);
    mSprite.setTexture(tAsteroid);
    mSprite.setTextureRect(sf::IntRect(0 + mMoveRect, 6, 64, 64));
    //color added for testing
    mSprite.setColor(sf::Color(255, 255, 0));
    mSprite.setOrigin(32, 32);
}

Asteroid::~Asteroid()
{
}

Asteroid::Asteroid(sf::Vector2f position, float angle, int level)
        : mLevel(level)
        , Entity(0, 0, ID_ASTEROID, ASTEROID_RADIUS, true)
{
    mDirection = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
    mSprite.setPosition(position);
    mSprite.setTexture(tAsteroid);
    mSprite.setTextureRect(sf::IntRect(0 + mMoveRect, 6, 64, 64));
    mSprite.setOrigin(32, 32);
    mMoveRect = 64;
    mSprite.setScale(level == 2 ? mSprite.getScale() * ASTEROID_RESCALE_RADIUS_FACTOR * ASTEROID_RESCALE_RADIUS_FACTOR
                               : mSprite.getScale() * ASTEROID_RESCALE_RADIUS_FACTOR);
    level == 2 ? mRadius *= ASTEROID_RESCALE_RADIUS_FACTOR* ASTEROID_RESCALE_RADIUS_FACTOR
               : mRadius *= ASTEROID_RESCALE_RADIUS_FACTOR;
}

bool Asteroid::Init(const std::string& ImageFile)
{
    init_done = true;
    return tAsteroid.loadFromFile(ImageFile);
}

int Asteroid::getLevel()
{
    return mLevel;
}

void Asteroid::breakDown()
{
    mLevel++;

    if (mLevel > 2)
    {
        mAlive = false;
        return;
    }

    mSprite.setScale(mSprite.getScale() * ASTEROID_RESCALE_RADIUS_FACTOR);
    mRadius *= 0.75f;
    int angle = rand() % 360;
    mDirection = sf::Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
}

void Asteroid::update(sf::Time& elapsedTime)
{
    if (!mAlive)
        return;

    if (mMoveRect >= 1024)
    {
        mMoveRect    = 0;
        mElapsedTime = 0;
    }
    mSprite.setTextureRect(sf::IntRect(0 + mMoveRect, 6, 64, 64));

    float frametime = 125.0f / 60.0f;
    if (mElapsedTime >= frametime)
    {
        mMoveRect += 64;
        mElapsedTime = 0;
    }
    ++mElapsedTime;

    sf::Vector2f distance = mDirection * speed[ mLevel ] * (float)elapsedTime.asMilliseconds();
    mSprite.move(distance);

    sf::Vector2f position = mSprite.getPosition();

    if (position.x > W_WIDTH)
        position.x = 0;
    if (position.x < 0)
        position.x = W_WIDTH;

    if (position.y > W_HEIGHT)
        position.y = 0;
    if (position.y < 0)
        position.y = W_HEIGHT;

    mSprite.setPosition(position);
}
