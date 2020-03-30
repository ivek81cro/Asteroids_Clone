#include "Ship.h"

const float Ship::acceleration   = 5.0f;
const float Ship::max_speed      = 10.0f;
const float Ship::rotation_speed = 0.15f;

Ship::Ship()
        : mXmove(0)
        , mYmove(0)
        , mSpeed(0, 0)
{

    Reset();
}

Ship::~Ship()
{
}

void Ship::Reset()
{
    mShipTexture.loadFromFile(SHIP_TEXTURE);
    mSprite.setTexture(mShipTexture);
    mSprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
    mSprite.setOrigin(20, 20);
    mSprite.setPosition(W_WIDTH / 2, W_HEIGHT / 2);
    mSprite.setRotation(0.0f);
    mSpeed.x      = 0;
    mSpeed.y      = 0;
    mAlive     = true;
    mMoveRect    = 0;
    mElapsedTime = 0;
    mRadius       = 0;
}

void Ship::Update(sf::Time& elapsedTime, const sf::Event& event)
{
    if (!mAlive)
    {
        ShipExplode(elapsedTime);
    }
    else
    {
        MoveShip(elapsedTime, event);
        mSprite.move(mSpeed);
    }

    if (mAlive && mRadius == 0)
    {
        ShieldsUp(elapsedTime);
    }
    mSprite.setPosition(CheckPosition());
}

void Ship::OnEvent(const sf::Event& event)
{
    mXmove = 0;
    mYmove = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        mYmove += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        mXmove = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        mYmove += -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        mXmove = -1;
}

void Ship::MoveShip(sf::Time& elapsedTime, const sf::Event& event)
{
    if (mXmove != 0)
    {
        mSprite.rotate(mXmove * rotation_speed * elapsedTime.asMilliseconds());
    }

    if (mYmove != 0)
    {
        float rotation = mSprite.getRotation() - 90;
        float x_speed  = cos(rotation * DEGTORAD);
        float y_speed  = sin(rotation * DEGTORAD);

        mSpeed.x += mYmove * acceleration * elapsedTime.asSeconds() * x_speed;
        mSpeed.y += mYmove * acceleration * elapsedTime.asSeconds() * y_speed;
        if ((mSpeed.x * mSpeed.x) > (max_speed * max_speed))
            mSpeed.x = mSpeed.x > 0 ? max_speed : -max_speed;
        if ((mSpeed.y * mSpeed.y) > (max_speed * max_speed))
            mSpeed.y = mSpeed.y > 0 ? max_speed : -max_speed;

        if (mYmove == 1)
            mSprite.setTextureRect(sf::IntRect(40, 40, 40, 40));
        if (mYmove == -1)
            mSprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
    }
    if (mXmove == 0 && mYmove == 0)
    {
        //Drag
        mSpeed.x *= 0.995f;
        mSpeed.y *= 0.995f;

        mSprite.setTextureRect(sf::IntRect(40, 85, 40, 40));
    }
}

sf::Vector2f Ship::CheckPosition()
{
    sf::Vector2f position = mSprite.getPosition();

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

void Ship::Kill()
{
    mAlive = false;
}

void Ship::ShipExplode(sf::Time& elapsedTime)
{
    if (mMoveRect >= 950)
    {
        Reset();
    }
    else
    {
        mShipTexture.loadFromFile(SHIP_EXPLOSION_TEXTURE);
        mSprite.setTexture(mShipTexture);
        mSprite.setTextureRect(sf::IntRect(0 + mMoveRect, 0, 50, 50));
        mSprite.setOrigin(20, 20);

        float frametime = 4.0f / 60.0f;
        if (mElapsedTime >= frametime)
        {
            mMoveRect += 50;
            mElapsedTime -= frametime;
        }
        mElapsedTime += elapsedTime.asSeconds();
    }
}

void Ship::ShieldsUp(sf::Time& elapsedTime)
{
    float frametime = 240.0f / 60.0f;
    if (mElapsedTime >= frametime)
    {
        mRadius       = SHIP_RADIUS;
        mElapsedTime = 0;
    }
    mElapsedTime += elapsedTime.asSeconds();
}
