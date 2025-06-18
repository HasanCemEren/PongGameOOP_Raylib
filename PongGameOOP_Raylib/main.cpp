#include <raylib.h>
#include "Game.h"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(144);

    Game game;
    game.Init(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        game.Draw(screenWidth, screenHeight);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
