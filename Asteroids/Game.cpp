#include "Game.h"
#include "Constants.h"

Game::Game():running(true), lives(3) {}

Game::~Game()
{
	window.close();
}

int Game::run()
{
	createWindow();

	sf::Clock clock;
	sf::Texture tBackground;
	tBackground.loadFromFile("images/background.jpg");
	sf::Sprite sBackground(tBackground);

	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT_SUCCESS;
			}
			ship.onEvent(event);
		}
		window.clear();
		ship.update(clock.restart().asMilliseconds());
		window.draw(sBackground);
		window.draw(ship);
		window.display();
	}
	return EXIT_SUCCESS;
}

void Game::createWindow()
{
	if (window.isOpen())
		window.close();

	window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Close);
	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(W_FPSLIMIT);
}