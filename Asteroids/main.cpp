#include "Constants.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
    srand(time(NULL));

    Game game;
    game.Run();

    return EXIT_SUCCESS;
}
