#include "Ship.h"

const float Ship::acceleration = 5.0f;
const float Ship::max_speed = 10.0f;
const float Ship::rotation_speed = 0.15f;

Ship::Ship()
{
	radius = SHIP_RADIUS;

	x_move = 0;
	y_move = 0;

	reset();
}

Ship::~Ship() {}

void Ship::reset()
{
	tShip.loadFromFile(SHIP_TEXTURE);
	sShip.setTexture(tShip);
	sShip.setTextureRect(sf::IntRect(40, 0, 40, 40));
	sShip.setOrigin(20, 20);
	setPosition(W_WIDTH / 2, W_HEIGHT / 2);
	setRotation(0.0f);
	speed.x = 0;
	speed.y = 0;
	is_alive = true;
	ran = 0;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sShip, states);
}

void Ship::update(float frametime, const sf::Event& event)
{
	if (!is_alive) 
	{
		shipExplode();
	}
	else
	{
		moveShip(frametime, event);
		move(speed);
	}

	setPosition(checkPosition());
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

void Ship::moveShip(float frametime, const sf::Event& event)
{
	if (x_move != 0)
	{
		rotate(x_move * rotation_speed * frametime);
	}

	if (y_move != 0)
	{
		float rotation = getRotation() - 90;
		float x_speed = cos(rotation * DEGTORAD);
		float y_speed = sin(rotation * DEGTORAD);

		speed.x += y_move * acceleration * frametime * x_speed / 1000;
		speed.y += y_move * acceleration * frametime * y_speed / 1000;
		if ((speed.x * speed.x) > (max_speed * max_speed))
			speed.x = speed.x > 0 ? max_speed : -max_speed;
		if ((speed.y * speed.y) > (max_speed * max_speed))
			speed.y = speed.y > 0 ? max_speed : -max_speed;

		if (y_move == 1)
			sShip.setTextureRect(sf::IntRect(40, 40, 40, 40));
		if (y_move == -1)
			sShip.setTextureRect(sf::IntRect(40, 0, 40, 40));
		//drag
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			speed.x *= 0.997f;
			speed.y *= 0.997f;
		}
	}
	if (x_move == 0 && y_move == 0)
		sShip.setTextureRect(sf::IntRect(40, 85, 40, 40));
}

sf::Vector2f Ship::checkPosition()
{
	sf::Vector2f position = getPosition();

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

void Ship::shipExplode()
{
	if (ran >= 950)
		reset();
	else 
	{
		tShip.loadFromFile(SHIP_EXPLOSION_TEXTURE);
		sShip.setTexture(tShip);
		sShip.setTextureRect(sf::IntRect(0 + ran, 0, 50, 50));
		sShip.setOrigin(20, 20);

		if (tick % 4 == 0)
			ran += 50;
		++tick;
	}
}