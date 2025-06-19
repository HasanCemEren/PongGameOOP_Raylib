#include "Game.h"
#include <raylib.h>

int main() {
    InitWindow(1280, 800, "OOP Pong");
    SetTargetFPS(144);

    Game game;
    game.Run();

    CloseWindow();
    return 0;
}
