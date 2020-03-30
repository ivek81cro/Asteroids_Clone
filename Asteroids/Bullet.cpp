#include "Bullet.h"
#include "Constants.h"

const float Bullet::lifetime = 1000.0f;
const float Bullet::speed    = 0.9f;
bool        Bullet::init_done;
sf::Texture Bullet::tBullet;

Bullet::Bullet(sf::Vector2f position, float angle)
        : mRemainingLife(lifetime)
        , mDirection(cos(angle * DEGTORAD), sin(angle * DEGTORAD))
        , Entity(0,0,ID_BULLET,BULLET_RADIUS, true)
{
    if (!init_done)
        init(BULLET_TEXTURE);

    mSprite.setPosition(position);
    mSprite.setRotation(angle + 90);
    mSprite.setScale(0.25f, 0.25f);
    mSprite.setTexture(tBullet);
    mSprite.setTextureRect(sf::IntRect(0, 0, 14, 44));
    mSprite.setOrigin(7, 22);
}

Bullet::~Bullet()
{
}

void Bullet::update(sf::Time& elapsedTime)
{
    if (!mAlive)
        return;

    mRemainingLife -= elapsedTime.asMilliseconds();
    if (mRemainingLife <= 0)
        mAlive = false;

    sf::Vector2f distance = mDirection * speed * (float)elapsedTime.asMilliseconds();

    mSprite.move(distance);
}

bool Bullet::init(const std::string& ImageFile)
{
    init_done = true;
    return tBullet.loadFromFile(ImageFile);
}

void Bullet::kill()
{
    mAlive = false;
}
