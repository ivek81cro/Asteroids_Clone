#include "Ship.h"

const float Ship::acceleration   = 5.0f;
const float Ship::max_speed      = 10.0f;
const float Ship::rotation_speed = 0.15f;

Ship::Ship()
        : x_move(0)
        , y_move(0)
        , speed(0, 0)
{

    reset();
}

Ship::~Ship()
{
}

void Ship::reset()
{
    tShip.loadFromFile(SHIP_TEXTURE);
    sprite.setTexture(tShip);
    sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
    sprite.setOrigin(20, 20);
    sprite.setPosition(W_WIDTH / 2, W_HEIGHT / 2);
    sprite.setRotation(0.0f);
    speed.x      = 0;
    speed.y      = 0;
    is_alive     = true;
    mMoveRect    = 0;
    mElapsedTime = 0;
    radius       = 0;
}

void Ship::update(sf::Time& elapsedTime, const sf::Event& event)
{
    if (!is_alive)
    {
        shipExplode(elapsedTime);
    }
    else
    {
        moveShip(elapsedTime, event);
        sprite.move(speed);
    }

    if (is_alive && radius == 0)
    {
        shieldsUp(elapsedTime);
    }
    sprite.setPosition(checkPosition());
}

void Ship::onEvent(const sf::Event& event)
{
    x_move = 0;
    y_move = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        y_move += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x_move = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        y_move += -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        x_move = -1;
}

void Ship::moveShip(sf::Time& elapsedTime, const sf::Event& event)
{
    if (x_move != 0)
    {
        sprite.rotate(x_move * rotation_speed * elapsedTime.asMilliseconds());
    }

    if (y_move != 0)
    {
        float rotation = sprite.getRotation() - 90;
        float x_speed  = cos(rotation * DEGTORAD);
        float y_speed  = sin(rotation * DEGTORAD);

        speed.x += y_move * acceleration * elapsedTime.asSeconds() * x_speed;
        speed.y += y_move * acceleration * elapsedTime.asSeconds() * y_speed;
        if ((speed.x * speed.x) > (max_speed * max_speed))
            speed.x = speed.x > 0 ? max_speed : -max_speed;
        if ((speed.y * speed.y) > (max_speed * max_speed))
            speed.y = speed.y > 0 ? max_speed : -max_speed;

        if (y_move == 1)
            sprite.setTextureRect(sf::IntRect(40, 40, 40, 40));
        if (y_move == -1)
            sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
    }
    if (x_move == 0 && y_move == 0)
    {
        //Drag
        speed.x *= 0.995f;
        speed.y *= 0.995f;

        sprite.setTextureRect(sf::IntRect(40, 85, 40, 40));
    }
}

sf::Vector2f Ship::checkPosition()
{
    sf::Vector2f position = sprite.getPosition();

    if (position.x > W_WIDTH)
        position.x = 0;
    if (position.x < 0)
        position.x = W_WIDTH;

    if (position.y > W_HEIGHT)
        position.y = 0;
    if (position.y < 0)
        position.y = W_HEIGHT;

    return position;
}

void Ship::kill()
{
    is_alive = false;
}

void Ship::shipExplode(sf::Time& elapsedTime)
{
    if (mMoveRect >= 950)
    {
        reset();
    }
    else
    {
        tShip.loadFromFile(SHIP_EXPLOSION_TEXTURE);
        sprite.setTexture(tShip);
        sprite.setTextureRect(sf::IntRect(0 + mMoveRect, 0, 50, 50));
        sprite.setOrigin(20, 20);

        float frametime = 4.0f / 60.0f;
        if (mElapsedTime >= frametime)
        {
            mMoveRect += 50;
            mElapsedTime -= frametime;
        }
        mElapsedTime += elapsedTime.asSeconds();
    }
}

void Ship::shieldsUp(sf::Time& elapsedTime)
{
    float frametime = 240.0f / 60.0f;
    if (mElapsedTime >= frametime)
    {
        radius       = SHIP_RADIUS;
        mElapsedTime = 0;
    }
    mElapsedTime += elapsedTime.asSeconds();
}
