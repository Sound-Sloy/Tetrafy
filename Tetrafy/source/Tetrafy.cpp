#include "Game.h"

int main()
{
    Game game(Globals::BaseWindowSizeX, Globals::BaseWindowSizeY, "Tetrafy");
    while (!game.GameShouldClose()) {
        game.Tick();
    }
}

int WinMain() {
    main();
}