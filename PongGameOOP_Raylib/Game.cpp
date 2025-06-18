#include "Game.h"
#include <raylib.h>
#include "Game.h"

extern int playerScore;
extern int cpuScore;

Color green = { 38, 185, 154, 255 };
Color darkGreen = { 20, 160, 133, 255 };
Color lightGreen = { 129, 204, 184, 255 };

void Game::Init(int screenWidth, int screenHeight) {
    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 5;
    ball.speedY = 5;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;
}

void Game::Update() {
    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {
        ball.speedX *= -1;
    }

    if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height })) {
        ball.speedX *= -1;
    }
}

void Game::Draw(int screenWidth, int screenHeight) {
    ClearBackground(darkGreen);
    DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, green);
    DrawCircle(screenWidth / 2, screenHeight / 2, 150, lightGreen);
    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
    ball.Draw();
    cpu.Draw();
    player.Draw();
    DrawText(TextFormat("%i", cpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
}
