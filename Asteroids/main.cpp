#include "Constants.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
    srand(time(NULL));

    Game game;
    game.run();

    return EXIT_SUCCESS;
}
