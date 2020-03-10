#include <SFML/Graphics.hpp>

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(W, H), "Asteroids");
	window.setFramerateLimit(60);

	sf::Texture t1, t2;
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");

	sf::Sprite sPlayer(t1), sBackground(t2);
	sPlayer.setTextureRect(sf::IntRect(40, 0, 40, 40));
	sPlayer.setOrigin(20, 20);

	float x = 300, y = 300;
	float dx = 0, dy = 0, angle = 0;
	bool thrust, retro;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
			angle += 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
			angle -= 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
			thrust = true;
		else 
			thrust = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			retro = true;
		else
			retro = false;

		if (thrust)
		{
			dx += cos(angle * DEGTORAD) * 0.2;
			dy += sin(angle * DEGTORAD) * 0.2;
		}
		else if(retro)
		{
			dx -= cos(angle * DEGTORAD) * 0.2;
			dy -= sin(angle * DEGTORAD) * 0.2;
		}
		else
		{
			dx *= 0.90;
			dy *= 0.90;
		}

		int maxSpeed = 5;
		float speed = sqrt(dx * dx + dy * dy);
		
		if(speed>maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		x += dx;
		y += dy;

		if (x > W) x = 0; if (x < 0) x = W;
		if (y > H) y = 0; if (y < 0) y = H;

		sPlayer.setPosition(x, y);
		sPlayer.setRotation(angle + 90);

		window.clear();
		window.draw(sBackground);
		window.draw(sPlayer);
		window.display();
	}
	

	return 0;
}