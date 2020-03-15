#include "Ship.h"

const float Ship::acceleration = 5.0f;
const float Ship::max_speed = 15.0f;
const float Ship::rotation_speed = 0.15f;

Ship::Ship()
{
	tShip.loadFromFile("images/spaceship.png");
	sShip.setTexture(tShip);
	sShip.setTextureRect(sf::IntRect(40, 0, 40, 40));
	sShip.setOrigin(20, 20);

	x_move = 0;
	y_move = 0;

	reset();
}

Ship::~Ship() {}

void Ship::reset()
{
	setPosition(W_WIDTH / 2, W_HEIGHT / 2);
	setRotation(0.0f);
	speed.x = 0;
	speed.y = 0;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sShip, states);
}

void Ship::update(float frametime, const sf::Event& event)
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
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)||
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		speed.x *= 0.997;
		speed.y *= 0.997;
	}
	move(speed);

	sf::Vector2f position = getPosition();

	if (position.x > W_WIDTH)
		position.x = 0;
	if (position.x < 0)
		position.x = W_WIDTH;

	if (position.y > W_HEIGHT)
		position.y = 0;
	if (position.y < 0)
		position.y=W_HEIGHT;

	setPosition(position);
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



