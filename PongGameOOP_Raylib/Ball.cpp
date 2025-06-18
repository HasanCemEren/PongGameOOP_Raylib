#include "Ball.h"
#include "Game.h" // playerScore, cpuScore
#include <raylib.h>

extern int playerScore;
extern int cpuScore;

void Ball::Draw() {
    DrawCircle(x, y, radius, YELLOW);
}

void Ball::Update() {
    x += speedX;
    y += speedY;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        speedY *= -1;
    }

    if (x + radius >= GetScreenWidth()) {
        cpuScore++;
        ResetBall();
    }

    if (x - radius <= 0) {
        playerScore++;
        ResetBall();
    }
}

void Ball::ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speedChoices[] = { 1, -1 };
    speedX *= speedChoices[GetRandomValue(0, 1)];
    speedY *= speedChoices[GetRandomValue(0, 1)];
}
