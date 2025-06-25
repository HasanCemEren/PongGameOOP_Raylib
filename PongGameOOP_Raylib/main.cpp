#include "Game.h"
#include <raylib.h>
//Basic raylib structure
int main() {
    InitWindow(1280, 800, "Style Smash");
    SetTargetFPS(144);

    Game game;
    game.Run();

    CloseWindow();
    return 0;
}