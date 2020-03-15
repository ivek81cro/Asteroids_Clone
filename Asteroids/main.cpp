#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"

int main()
{
	srand(time(NULL));

	Game game;
	game.run();

	return EXIT_SUCCESS;
}