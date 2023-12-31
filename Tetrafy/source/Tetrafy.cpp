#include "Game.h"

int main()
{
    Game game(738, 800, "Tetrafy");
    while (!game.GameShouldClose()) {
        game.Tick();
    }
}

int WinMain() {
    main();
}