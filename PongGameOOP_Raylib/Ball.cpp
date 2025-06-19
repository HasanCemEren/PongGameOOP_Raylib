#include "Ball.h"
#include "GameState.h"
#include <raylib.h>

Ball::Ball() {
    radius = 20;
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    speedX = 5;
    speedY = 5;
}

void Ball::Update() {
    x += speedX;
    y += speedY;

    // �st ve alt duvarlara �arpma - Y h�z�n� ters �evir
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
        speedY *= -1;

    // Sa� duvara �arpma - CPU kazan�r
    if (x + radius >= GetScreenWidth()) {
        GameState::cpuScore++;
        Reset();
    }

    // Sol duvara �arpma - Player kazan�r  
    if (x - radius <= 0) {
        GameState::playerScore++;
        Reset();
    }
}

void Ball::Draw() const {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, YELLOW);
}

void Ball::Reset() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    // Random y�n se�imi - daha temiz kod
    int xDirection = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    int yDirection = (GetRandomValue(0, 1) == 0) ? -1 : 1;

    speedX = 5 * xDirection;
    speedY = 5 * yDirection;
}

// Paddle collision i�in - sadece X h�z�n� ters �evir
void Ball::ReverseSpeedX() {
    speedX *= -1;
}

int Ball::GetRadius() const {
    return radius;
}