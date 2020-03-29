#include "Bullet.h"
#include "Constants.h"

const float Bullet::lifetime = 1000.0f;
const float Bullet::speed    = 0.9f;
bool        Bullet::init_done;
sf::Texture Bullet::tBullet;

Bullet::Bullet(sf::Vector2f position, float angle)
        : remaning_life(lifetime)
        , direction(cos(angle * DEGTORAD), sin(angle * DEGTORAD))
{
    if (!init_done)
        Init(BULLET_TEXTURE);

    sprite.setPosition(position);
    sprite.setRotation(angle + 90);
    sprite.setScale(0.25f, 0.25f);

    sprite.setTexture(tBullet);
    sprite.setTextureRect(sf::IntRect(0, 0, 14, 44));
    sprite.setOrigin(7, 22);
    radius   = BULLET_RADIUS;
    is_alive = true;
    id       = ID_BULLET;
}

Bullet::~Bullet()
{
}

void Bullet::update(sf::Time& elapsedTime)
{
    if (!is_alive)
        return;

    remaning_life -= elapsedTime.asMilliseconds();
    if (remaning_life <= 0)
        is_alive = false;

    sf::Vector2f distance = direction * speed * (float)elapsedTime.asMilliseconds();

    sprite.move(distance);
}

bool Bullet::Init(const std::string& ImageFile)
{
    init_done = true;
    return tBullet.loadFromFile(ImageFile);
}

void Bullet::kill()
{
    is_alive = false;
}
